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

	

}

void ResourceManager::CreateDefaultMesh()
{

	std::shared_ptr<Mesh> mesh= std::make_shared<Mesh>(_device);
	mesh->SetName(L"Rectangle");
	mesh->CreateDefaultRectangle();
	Add(mesh->GetName(),mesh);

}

void ResourceManager::CreateDefaultShader()
{

}

void ResourceManager::CreateDefaultMaterial()
{

}

void ResourceManager::CreateDefaultAnimation()
{

}
