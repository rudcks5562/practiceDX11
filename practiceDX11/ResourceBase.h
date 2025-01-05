#pragma once



enum class ResourceType : uint8
{
	None = -1,
	Mesh,
	Shader,
	Texture,
	Material,
	Animation,

	End
};
enum {
	RESOURCE_TYPE_COUNT = static_cast<uint8>(ResourceType::End)
};


class ResourceBase : public std::enable_shared_from_this<ResourceBase>
{

public:
	ResourceBase(ResourceType type);
	virtual ~ResourceBase();
	ResourceType GetType() { return _type; }
	void SetName(const std::wstring& name) { _name = name; }
	const std::wstring& GetName() { return _name; }

	uint32 GetId() { return _id; }


protected:// file io-> ���ҽ��� ������ �ٸ��Ƿ� �����ε�
	virtual void Load(const std::wstring& path) {}
	virtual void Save(const std::wstring& path) {}

protected:
	ResourceType _type = ResourceType::None;
	std::wstring _name;
	std::wstring _path;
	uint32 _id = 0;



};
