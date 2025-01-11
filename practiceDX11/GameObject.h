#pragma once

class MonoBehavior;
class Transform;
class Camera;
class MeshRenderer;
class Animator;

class GameObject : public std::enable_shared_from_this<GameObject>
{

public:
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext>deviceContext);
	~GameObject();

	void Awake();
	void Start();
	void LateUpdate();
	void Update();
	void FixedUpdate();

	std::shared_ptr<Component> GetFixedComponent(ComponentType type);
	std::shared_ptr<Transform> GetTransform();
	std::shared_ptr<Camera> GetCamera();
	std::shared_ptr<MeshRenderer> GetMeshRenderer();
	std::shared_ptr<Transform> GetOrAddTransform();
	std::shared_ptr<Animator>GetAnimator();
	void AddComponent(std::shared_ptr<Component> component);


	//void Render(std::shared_ptr<Pipeline> pipeline);


private:

	ComPtr<ID3D11Device> _device;

	


protected:

	std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;//정적 크기
	std::vector<std::shared_ptr<MonoBehavior>> _scripts;//동적 개수



};