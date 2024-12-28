#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::Awake()
{
	for (const std::shared_ptr<GameObject>& gameObject: _gameObjects) {
		gameObject->Awake();
	}

}

void Scene::Start()
{
	for (const std::shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->Start();
	}
}

void Scene::Update()
{
	for (const std::shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const std::shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->LateUpdate();
	}
}

void Scene::FixedUpdate()
{
	for (const std::shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->FixedUpdate();
	}
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);

}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject)
{
	auto findIT = std::find(_gameObjects.begin(), _gameObjects.end(),gameObject);
	if (findIT != _gameObjects.end()) {
		_gameObjects.erase(findIT);
	}
}
