#include "stdafx.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Game.h"
#include "Pipeline.h"
#include "Mesh.h"


MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:_device(device),Super(ComponentType::MeshRenderer)
{


	_vertexShader = std::make_shared<VertexShader>(device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");//VS

	_inputLayout = std::make_shared<InputLayout>(device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());//input layout
	//_inputLayout->Create(VertexColorData::descs, _vertexShader->GetBlob());//input layout

	_pixelShader = std::make_shared<PixelShader>(device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");// PS

	//_vertexShader->Create(L"Color.hlsl", "VS", "vs_5_0");//VS

	_texture1 = std::make_shared<Texture>(device);
	_texture1->Create(L"Golem.png");


}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{



	//Render
	//Render(_pipeLine);
}


