#include "stdafx.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Game.h"
#include "Pipeline.h"
#include "Mesh.h"


MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:_device(device),Super(ComponentType::MeshRenderer)
{



	//_vertexShader->Create(L"Color.hlsl", "VS", "vs_5_0");//VS

	_texture1 = std::make_shared<Texture>(device);
	_texture1->Create(L"Golem.png");


}

MeshRenderer::~MeshRenderer()
{
}



