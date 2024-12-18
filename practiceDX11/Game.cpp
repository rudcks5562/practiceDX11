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

	_rasterizerState = std::make_shared<RasterizerState>(_graphics->GetDevice());
	_samplerState = std::make_shared<SamplerState>(_graphics->GetDevice());
	_blendState = std::make_shared<BlendState>(_graphics->GetDevice());

	_pipeline = std::make_shared<Pipeline>(_graphics->GetDeviceContext());

	//create geometry
	GeometryHelper::CreateRectangle(_geometry);

	// vertex buffer 
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer->Create(_geometry->GetIndices());//idx buff
		
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");//VS
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());//input layout

	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");// PS


	_texture1->Create(L"Golem.png");

	_rasterizerState->Create();
	_samplerState->Create();
	_blendState->Create();




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
	// 오브젝트 생성
// IA- VS- RS- PS- OM
	_graphics->RenderBegin();// 도화지 갱신
	{
		PipelineInfo info;
		info.inputLayout = _inputLayout;
		info.vertexShader = _vertexShader;
		info.pixelShader = _pixelShader;
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;

		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(_vertexBuffer);
		_pipeline->SetIndexBuffer(_indexBuffer);
		_pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
		_pipeline->SetTexture(0, SS_PixelShader, _texture1);
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);
		_pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);


	}

	_graphics->RenderEnd();



}

	//const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	//_graphics->GetDevice()->CreateInputLayout(layout,count,_vsBlob->GetBufferPointer(),_vsBlob->GetBufferSize(),_inputLayout.GetAddressOf());
	//3번째 인자가 쉐이더와 연관이 되어있기 때문에 쉐이더부터 만든다.
	//blob->쉐이더 연관.
	// input layout 
