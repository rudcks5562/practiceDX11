#pragma once
class GameObject;
class Transform;

enum class ComponentType : uint8 {
	Transform,
	MeshRenderer,
	Camera,
	Animator,
	//..
	Script,
	End,

};
enum {
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End) - 1
};


class Component
{
public:
	Component(ComponentType type);
	virtual ~Component();

	virtual void Awake() {}
	virtual void Start() {}
	virtual void LateUpdate() {}
	virtual void Update() {}
	virtual void FixedUpdate() {}


public:
	ComponentType GetType() { return _type; }

	std::shared_ptr<GameObject> GetGameObject();
	std::shared_ptr<Transform> GetTransform();

private:
	friend class GameObject;
	
	void SetGameObject(std::shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }


protected:
	ComponentType _type;
	std::weak_ptr<GameObject>_gameObject;

};

