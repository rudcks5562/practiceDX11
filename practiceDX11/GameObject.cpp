#include "stdafx.h"
#include "GameObject.h"
#include "MonoBehavior.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	:_device(device)
{
}

GameObject::~GameObject()
{
}

void GameObject::Awake()
{
	for (std::shared_ptr<Component>& component : _components) {
		if (component)
		component->Awake();
	}
	for (std::shared_ptr<MonoBehavior>& script : _scripts) {

		script->Awake();
	}
}

void GameObject::Start()
{
	for (std::shared_ptr<Component>& component : _components) {
		if (component)
			component->Start();
	}
	for (std::shared_ptr<MonoBehavior>& script : _scripts) {

		script->Start();
	}

}

void GameObject::LateUpdate()
{
	for (std::shared_ptr<Component>& component : _components) {
		if (component)
			component->LateUpdate();
	}
	for (std::shared_ptr<MonoBehavior>& script : _scripts) {

		script->LateUpdate();
	}
}

void GameObject::Update()
{

	for (std::shared_ptr<Component>& component : _components) {
		if (component)
			component->Update();
	}
	for (std::shared_ptr<MonoBehavior>& script : _scripts) {

		script->Update();
	}

	//temp
	{

		if (GetCamera()){
			return;
		}
	}


}

void GameObject::FixedUpdate()
{
	for (std::shared_ptr<Component>& component : _components) {
		if (component)
		component->FixedUpdate();
	}
	for (std::shared_ptr<MonoBehavior>& script : _scripts) {

		script->FixedUpdate();
	}
}

std::shared_ptr<Component> GameObject::GetFixedComponent(ComponentType type)
{

	uint8 index = static_cast<uint8>(type);

	assert(index < FIXED_COMPONENT_COUNT);

	return _components[index];
}

std::shared_ptr<Transform> GameObject::GetTransform()
{

	std::shared_ptr<Component>component = GetFixedComponent(ComponentType::Transform);

	return std::static_pointer_cast<Transform>(component);
}

std::shared_ptr<Camera> GameObject::GetCamera()
{
	std::shared_ptr<Component>component = GetFixedComponent(ComponentType::Camera);

	return std::static_pointer_cast<Camera>(component);
}

std::shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	std::shared_ptr<Component>component =	GetFixedComponent(ComponentType::MeshRenderer);

	return std::static_pointer_cast<MeshRenderer>(component);
} 

std::shared_ptr<Transform> GameObject::GetOrAddTransform()
{
	
	if (GetTransform() == nullptr) {
		std::shared_ptr<Transform> transform = std::make_shared<Transform>();
		AddComponent(transform);
	}

	return GetTransform();
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());// 스마트 포인터가 아니라this사용시 큰일남

		//생성자에서는 sharedfromthis를 사용하지 못한다.
	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT) {

		_components[index] = component;

	}
	else {
		_scripts.push_back(std::dynamic_pointer_cast<MonoBehavior>(component));
	}

}

