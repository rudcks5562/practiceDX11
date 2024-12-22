#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:_device(device)
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


	_constantBuffer = std::make_shared<ConstantBuffer<TransformData>>(device, deviceContext);
	_constantBuffer->Create();
	
	_texture1 = std::make_shared<Texture>(device);
	_texture1->Create(L"Golem.png");
	_samplerState = std::make_shared<SamplerState>(device);
	_samplerState->Create();
	
	//TEST CODE!!
	_parent->AddChild(_transform);
	_transform->SetParent(_parent);



}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	//_transformData.offset.x += 0.003f;
//_transformData.offset.y += 0.003f;


	// parent 위치만 건드려보는 테스트
	Vec3 pos = _parent->GetPosition();
	pos.x += 0.001f;
	_parent->SetPosition(pos);

	Vec3 rot = _parent->GetRotation();
	rot.z += 0.01f;
	_parent->SetRotation(rot);


	//Vec3 pos=_transform->GetPosition();
	//pos.x += 0.001f;
	//_transform->SetPosition(pos);

	/* 
		Matrix matScale = Matrix::CreateScale(_localScale / 3);
	Matrix matRoation = Matrix::CreateRotationX(_localRotation.x);
	matRoation *= Matrix::CreateRotationY(_localRotation.y);
	matRoation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);
	*/

	_transformData.matWorld = _transform->GetWorldMatrix();



	_constantBuffer->CopyData(_transformData);
}

void GameObject::Render(std::shared_ptr<Pipeline>pipeline)
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
	pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);
	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);

}
