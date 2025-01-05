#pragma once

#include "ResourceBase.h"

class Mesh;
class Animation;
class Shader;
class Texture;
class Material;


class ResourceManager
{
public:
	ResourceManager(ComPtr<ID3D11Device> device);

	void Init();

	template<typename T>
	std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path);
	template<typename T>
	bool Add(const std::wstring& key, std::shared_ptr<T> object);


	template<typename T>
	std::shared_ptr<T> Get(const std::wstring& key);

			
	
	//
	template<typename T>
	ResourceType GetResourceType();

private:

	void CreateDefaultTexture();
	void CreateDefaultMesh();
	void CreateDefaultShader();
	void CreateDefaultMaterial();
	void CreateDefaultAnimation();



private:


private:

	ComPtr<ID3D11Device> _device;

	using KeyObjMap=std::map<std::wstring, std::shared_ptr<ResourceBase>>;
	std::array<KeyObjMap, RESOURCE_TYPE_COUNT> _resources;
	// enum 인덱스에 일치시킨 목록
	//1번에는 메쉬 리소스 목록 2번에는 메터리얼 목록..
};


template<typename T>
std::shared_ptr<T>
ResourceManager::Load(const std::wstring& key, const std::wstring& path)
{
	auto objectType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())// 
		return std::static_pointer_cast<T>(findIt->second);
	 
	std::shared_ptr<T> object =std::make_shared<T>();
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
bool ResourceManager::Add(const std::wstring& key, std::shared_ptr<T> object)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return false;

	keyObjMap[key] = object;
	return true;
}

template<typename T>
std::shared_ptr<T> ResourceManager::Get(const std::wstring& key)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];
	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return std::static_pointer_cast<T>(findIt->second);


	return nullptr;
}

template<typename T>
ResourceType ResourceManager::GetResourceType()
{
	if (std::is_same_v<T, Mesh>)
		return ResourceType::Mesh;
	if (std::is_same_v<T, Shader>)
		return ResourceType::Shader;
	if (std::is_same_v<T, Texture>)
		return ResourceType::Texture;
	if (std::is_same_v<T, Material>)
		return ResourceType::Material;
	if (std::is_same_v<T, Animation>)
		return ResourceType::Animation;

	assert(false);
	return ResourceType::None;
}


