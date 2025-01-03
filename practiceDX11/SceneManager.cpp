#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h" 
#include "Game.h"



SceneManager::SceneManager(std::shared_ptr<Graphics> graphics):_graphics(graphics)
{
}

void SceneManager::Init()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Awake();
	_activeScene->Start();



}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;
	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FixedUpdate();// ����



}

void SceneManager::LoadScene(std::wstring sceneName)
{
	//resource

	_activeScene = LoadTestScene();
	Init();
}

void SceneManager::Render()
{



}

std::shared_ptr<Scene> SceneManager::LoadTestScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

	std::shared_ptr<GameObject> camera = std::make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	camera->GetOrAddTransform();
	camera->AddComponent(
		std::make_shared<Camera>());
	scene->AddGameObject(camera);


	std::shared_ptr<GameObject> monster = std::make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	monster->GetOrAddTransform();
	std::shared_ptr<Pipeline> pp = GGame->GetPipeLine();
	monster->AddComponent(std::make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext(),GGame->GetPipeLine()));

	scene->AddGameObject(monster);




	return scene;
}
