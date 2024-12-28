#include "stdafx.h"
#include "MeshRenderer.h"
#include "Camera.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:_device(device),Super(ComponentType::MeshRenderer)
{ 
	_geometry = std::make_shared<Geometry<VertexTextureData>>();
	//_geometry = std::make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateRectangle(_geometry);
	//GeometryHelper::CreateRectangle(_geometry,Color{1.0f,0.f,0.f,1.0f});
	_vertexBuffer = std::make_shared<VertexBuffer>(device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = std::make_shared<IndexBuffer>(device);
	_indexBuffer->Create(_geometry->GetIndices());//idx buff

	_vertexShader = std::make_shared<VertexShader>(device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");//VS
	//_vertexShader->Create(L"Color.hlsl", "VS", "vs_5_0");//VS


	_inputLayout = std::make_shared<InputLayout>(device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());//input layout
	//_inputLayout->Create(VertexColorData::descs, _vertexShader->GetBlob());//input layout


	_pixelShader = std::make_shared<PixelShader>(device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");// PS

	_rasterizerState = std::make_shared<RasterizerState>(device);
	_rasterizerState->Create();

	_blendState = std::make_shared<BlendState>(device);
	_blendState->Create();


	_transformBuffer = std::make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
	_transformBuffer->Create();

	_cameraBuffer = std::make_shared<ConstantBuffer<CameraData>>(device, deviceContext);
	_cameraBuffer->Create();

	_texture1 = std::make_shared<Texture>(device);
	_texture1->Create(L"Golem.png");
	_samplerState = std::make_shared<SamplerState>(device);
	_samplerState->Create();

}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{

	_cameraData.matView = Camera::S_MatView;

	_cameraData.matProjection = Camera::S_MatProjection;
	_cameraBuffer->CopyData(_cameraData);

	_transformData.matWorld = GetTransform()->GetWorldMatrix();
	_transformBuffer->CopyData(_transformData);
}

void MeshRenderer::Render(std::shared_ptr<Pipeline> pipeline)
{
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;

	pipeline->UpdatePipeline(info);

	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetIndexBuffer(_indexBuffer);
	pipeline->SetConstantBuffer(1, SS_VertexShader, _transformBuffer);
	pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraBuffer);

	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);
	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);

}
