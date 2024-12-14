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
	//_graphics = make_shared<Graphics>(hwnd);
	_graphics = new Graphics(hwnd);
	_vertexBuffer = new VertexBuffer(_graphics->GetDevice());
	_indexBuffer = new IndexBuffer(_graphics->GetDevice());
	_inputLayout = new InputLayout(_graphics->GetDevice());


	CreateGeometry();
	CreateVS();
	CreateInputLayout();
	CreatePS();

	CreateRasterizerState();
	CreateSamplerState();
	CreateBlendState();

	CreateSRV();
	CreateConstantBuffer();

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


	D3D11_MAPPED_SUBRESOURCE subResource;
	ZeroMemory(&subResource, sizeof(subResource));


	_graphics->GetDeviceContext()->Map(_constantBuffer.Get(),0, D3D11_MAP_WRITE_DISCARD, 0,&subResource);
	::memcpy(subResource.pData, &_transformData, sizeof(_transformData));
	_graphics->GetDeviceContext()->Unmap(_constantBuffer.Get(), 0);

}

void Game::Render()
{

	_graphics->RenderBegin();// 도화지 갱신
	// 오브젝트 생성
	// IA- VS- RS- PS- OM
	{
		//IA (setting?) 
		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;
		
		auto _deviceContext = _graphics->GetDeviceContext();

		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetInputLayout(_inputLayout->GetComPtr().Get());
		// topology?
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// VS 
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_deviceContext->VSSetConstantBuffers(0,1,_constantBuffer.GetAddressOf());

		//RS
		// vs가넘겨준 삼각형 내부 픽셀판별

		_deviceContext->RSSetState(_rasterizerState.Get());//bind? 



		//PS
		_deviceContext->PSSetShader(_pixelShader.Get(),nullptr, 0);
		_deviceContext->PSSetShaderResources(0,1,_shaderResourceView.GetAddressOf());
		_deviceContext->PSSetShaderResources(1, 1, _shaderResourceView2.GetAddressOf());
		_deviceContext->PSSetSamplers(0,1,_samplerState.GetAddressOf());
		
		//리소스연결
		//OM
		_deviceContext->OMSetBlendState(_blendState.Get(),nullptr,0xFFFFFFFF);



		//_deviceContext->Draw(_vertices.size(),0);
		_deviceContext->DrawIndexed(_indices.size(), 0, 0);
		// IDX buff 추가까지는 잘됨.



	}

	_graphics->RenderEnd();



}

void Game::CreateGeometry() {// 삼각형 데이터 형성.

	//13
	//02


	_vertices.resize(4);// 삼각형이므로 점 3개
	_vertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
	_vertices[0].uv = Vec2(0.f,1.f);
	//_vertices[0].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA

	_vertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
	//_vertices[1].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA
	_vertices[1].uv = Vec2(0.f, 0.f);

	_vertices[2].position = Vec3(0.5f, -0.5f, 0.f);
	//_vertices[2].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA
	_vertices[2].uv = Vec2(1.f, 1.f);

	_vertices[3].position = Vec3(0.5f, 0.5f, 0.f);
	//_vertices[3].color = Color(1.0f, 0.f, 0.f, 1.f);// RGBA
	_vertices[3].uv = Vec2(1.f, 0.f);



	// vertex buffer 

		
	{
		_vertexBuffer->Create(_vertices);

	}


	//idx 

	{
		_indices = { 0,1,2,2,1,3 };


	}
	//idx buff
	{

		_indexBuffer->Create(_indices);
	}



}
void Game::CreateInputLayout() {// uv추가과정 

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout  {
	
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		//{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}// uv = float*2 이므로 r32g32로


	};// float = 4byte, 3*float = 12byte, 12 offset


	_inputLayout->Create(layout,_vsBlob);


	//const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	//_graphics->GetDevice()->CreateInputLayout(layout,count,_vsBlob->GetBufferPointer(),_vsBlob->GetBufferSize(),_inputLayout.GetAddressOf());
	//3번째 인자가 쉐이더와 연관이 되어있기 때문에 쉐이더부터 만든다.
	//blob->쉐이더 연관.


}

void Game::CreateVS()
{
	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0",_vsBlob);

	HRESULT hr= _graphics->GetDevice()->CreateVertexShader(_vsBlob->GetBufferPointer(),
		_vsBlob->GetBufferSize(),nullptr,_vertexShader.GetAddressOf()
		);

	assert(SUCCEEDED(hr));
}

void Game::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);

	HRESULT hr = _graphics->GetDevice()->CreatePixelShader(_psBlob->GetBufferPointer(),
		_psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf()
	);
	assert(SUCCEEDED(hr));


}

void Game::CreateSRV()
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	HRESULT hr=::LoadFromWICFile(L"Golem.png", WIC_FLAGS_NONE, &md, img);// img load
	assert(SUCCEEDED(hr));

	hr = ::CreateShaderResourceView(_graphics->GetDevice().Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());
	assert(SUCCEEDED(hr));
	//sec srv2

	 hr = ::LoadFromWICFile(L"123.png", WIC_FLAGS_NONE, &md, img);// img load
	assert(SUCCEEDED(hr));

	hr = ::CreateShaderResourceView(_graphics->GetDevice().Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView2.GetAddressOf());
	assert(SUCCEEDED(hr));

}

void Game::CreateConstantBuffer()
{

	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DYNAMIC;//cpu wr+ gpu read
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// 용도적시 
	desc.ByteWidth = sizeof(TransformData);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


	HRESULT hr = _graphics->GetDevice()->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));



}

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

void Game::LoadShaderFromFile(const std::wstring& path, const std::string& name, const std::string& version, ComPtr<ID3DBlob>& blob)
{

	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;



	HRESULT hr=::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(),
		nullptr
	);

	assert(SUCCEEDED(hr));

}



