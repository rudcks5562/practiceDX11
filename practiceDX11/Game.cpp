#include "stdafx.h"
#include "Game.h"


//class Graphics;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(HWND hwnd)
{
	_hwnd = hwnd;
	_graphics = std::make_shared<Graphics>(hwnd);
	//_graphics = new Graphics(hwnd);
	_vertexBuffer = std::make_shared<VertexBuffer>(_graphics->GetDevice());
	_indexBuffer = std::make_shared<IndexBuffer>(_graphics->GetDevice());
	_inputLayout = std::make_shared<InputLayout>(_graphics->GetDevice());
	_geometry = std::make_shared<Geometry<VertexTextureData>>();
	_vertexShader = std::make_shared<VertexShader>(_graphics->GetDevice());
	_pixelShader = std::make_shared<PixelShader>(_graphics->GetDevice());

	_constantBuffer = std::make_shared<ConstantBuffer<TransformData>>(_graphics->GetDevice(), _graphics->GetDeviceContext());

	_texture1 = std::make_shared<Texture>(_graphics->GetDevice());

	//create geometry
	GeometryHelper::CreateRectangle(_geometry);

	// vertex buffer 
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer->Create(_geometry->GetIndices());//idx buff
		
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");//VS
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());//input layout

	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");// PS


	_texture1->Create(L"Golem.png");



	CreateRasterizerState();
	CreateSamplerState();
	CreateBlendState();




	_constantBuffer->Create();

}

void Game::update()
{

	//_transformData.offset.x += 0.003f;
	//_transformData.offset.y += 0.003f;
	_localPosition.x += 0.001f;
	Matrix matScale =Matrix::CreateScale(_localScale/3);
	Matrix matRoation = Matrix::CreateRotationX(_localRotation.x);
	 matRoation *= Matrix::CreateRotationY(_localRotation.y);
	 matRoation *= Matrix::CreateRotationZ(_localRotation.z);
	 Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	 
	 Matrix matWorld = matScale * matRoation * matTranslation;//SRT 
	 _transformData.matWorld = matWorld;



	_constantBuffer->CopyData(_transformData);
}

void Game::Render()
{

	_graphics->RenderBegin();// 도화지 갱신
	// 오브젝트 생성
	// IA- VS- RS- PS- OM
	{
		//IA (setting?) 
		uint32 stride = sizeof(VertexTextureData);
		uint32 offset = 0;
		
		auto _deviceContext = _graphics->GetDeviceContext();

		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetInputLayout(_inputLayout->GetComPtr().Get());
		// topology?
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// VS 
		_deviceContext->VSSetShader(_vertexShader->GetComPtr().Get(), nullptr, 0);
		_deviceContext->VSSetConstantBuffers(0,1,_constantBuffer->GetComPtr().GetAddressOf());

		//RS
		// vs가넘겨준 삼각형 내부 픽셀판별

		_deviceContext->RSSetState(_rasterizerState.Get());//bind? 



		//PS
		_deviceContext->PSSetShader(_pixelShader->GetComPtr().Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0,1,_texture1->GetComPtr().GetAddressOf());
		//_deviceContext->PSSetShaderResources(1, 1, _shaderResourceView2.GetAddressOf());
		_deviceContext->PSSetSamplers(0,1,_samplerState.GetAddressOf());
		
		//리소스연결
		//OM
		_deviceContext->OMSetBlendState(_blendState.Get(),nullptr,0xFFFFFFFF);



		//_deviceContext->Draw(_vertices.size(),0);
		_deviceContext->DrawIndexed(_geometry->GetIndices().size(), 0, 0);
		// IDX buff 추가까지는 잘됨.



	}

	_graphics->RenderEnd();



}

	//const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	//_graphics->GetDevice()->CreateInputLayout(layout,count,_vsBlob->GetBufferPointer(),_vsBlob->GetBufferSize(),_inputLayout.GetAddressOf());
	//3번째 인자가 쉐이더와 연관이 되어있기 때문에 쉐이더부터 만든다.
	//blob->쉐이더 연관.
	// input layout 


void Game::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc)); 
	desc.FillMode = D3D11_FILL_SOLID;// wireframe option은 외곽?삼각형만 보여줌.
	desc.CullMode = D3D11_CULL_BACK;// 컬링->스킵 (후면인식시 그리지않겠다),프론트
	desc.FrontCounterClockwise=false;// 이걸로 전후면 판단(앞방향이 반시계인지 묻는 것)


	HRESULT hr =
		_graphics->GetDevice()->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());

	assert(SUCCEEDED(hr));

}

void Game::CreateSamplerState()
{

	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 1;//rgba
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	//
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.MaxAnisotropy = 16;
	desc.MaxLOD = FLT_MAX;
	desc.MinLOD = FLT_MIN;


	_graphics->GetDevice()->CreateSamplerState(&desc,_samplerState.GetAddressOf());






}

void Game::CreateBlendState()
{

	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BLEND));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;

	desc.RenderTarget[0].BlendEnable = true; 
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = _graphics->GetDevice()->CreateBlendState(&desc,_blendState.GetAddressOf());


	assert(SUCCEEDED(hr));



}





