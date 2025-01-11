#include "stdafx.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "mesh.h"
#include "Shader.h"
#include "Animation.h"
#include "Material.h"

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device):_device(device)
{
}

void ResourceManager::Init()
{
	CreateDefaultTexture();
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultMaterial();
	CreateDefaultAnimation();
}

void ResourceManager::CreateDefaultTexture()
{
	{
		auto texture = std::make_shared<Texture>(_device);
		texture->SetName(L"Golem");
		texture->Create(L"Golem.png");
		Add(texture->GetName(), texture);
	}
	{
		auto texture = std::make_shared<Texture>(_device);
		texture->SetName(L"Snake");
		texture->Create(L"Snake.bmp");
		Add(texture->GetName(), texture);
	}
	

}

void ResourceManager::CreateDefaultMesh()
{

	shared_ptr<Mesh> mesh = make_shared<Mesh>(_device);
	mesh->SetName(L"Rectangle");
	mesh->CreateDefautRectangle();
	Add(mesh->GetName(), mesh);

}

void ResourceManager::CreateDefaultShader()
{
	auto vertexShader = std::make_shared<VertexShader>(_device);
	vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");//VS

	auto inputLayout = std::make_shared<InputLayout>(_device);
	inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());//input layout
	//_inputLayout->Create(VertexColorData::descs, _vertexShader->GetBlob());//input layout

	auto pixelShader = std::make_shared<PixelShader>(_device);
	pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");// PS

	// shader

	shared_ptr<Shader> shader = make_shared<Shader>();
	shader->SetName(L"Default");
	shader->_vertexShader = vertexShader;
	shader->_inputLayout = inputLayout;
	shader->_pixelShader = pixelShader;
	Add(shader->GetName(), shader);


}

void ResourceManager::CreateDefaultMaterial()
{
	shared_ptr<Material> material = make_shared<Material>();
	material->SetName(L"Default");
	material->SetShader(Get<Shader>(L"Default"));

	material->SetTexture(Get<Texture>(L"Golem"));
	Add(material->GetName(), material);


}

void ResourceManager::CreateDefaultAnimation()
{

	shared_ptr<Animation> animation = make_shared<Animation>();
	animation->SetName(L"SnakeAnim");
	animation->SetTexture(Get<Texture>(L"Snake"));
	animation->SetLoop(true);


	animation->AddKeyFrame(keyFrame{ Vec2{0.f,0.f},Vec2{100.f,100.f},0.1f});
	animation->AddKeyFrame(keyFrame{ Vec2{100.f,0.f},Vec2{100.f,100.f},0.1f });
	animation->AddKeyFrame(keyFrame{ Vec2{200.f,0.f},Vec2{100.f,100.f},0.1f });
	animation->AddKeyFrame(keyFrame{ Vec2{300.f,0.f},Vec2{100.f,100.f},0.1f });

	Add(animation->GetName(), animation);
	//xml

}
