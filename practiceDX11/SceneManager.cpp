#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Animator.h"

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
	_activeScene->FixedUpdate();// ¹°¸®



}

void SceneManager::LoadScene(std::wstring sceneName)
{
	//resource

	_activeScene = LoadTestScene();
	Init();
}


#include "CameraMove.h"
std::shared_ptr<Scene> SceneManager::LoadTestScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();



	std::shared_ptr<GameObject> camera = std::make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	camera->GetOrAddTransform();
	camera->AddComponent(
		std::make_shared<Camera>());
	scene->AddGameObject(camera);
	{
		//camera->AddComponent(make_shared<CameraMove>());
	}

	// Monster
	{
		shared_ptr<GameObject> monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		monster->GetOrAddTransform()->SetPosition(Vec3{ 1.f, 1.f, 0.f });
		{
			monster->GetOrAddTransform();
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			monster->AddComponent(meshRenderer);
			auto material = RESOURCES->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);
			auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);
		}
		{
			auto animator = make_shared<Animator>();
			monster->AddComponent(animator);
			auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(monster);
	}

	// Monster
	{
		shared_ptr<GameObject> monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			monster->GetOrAddTransform();
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			monster->AddComponent(meshRenderer);
			auto material = RESOURCES->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);
			auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);
		}
		{
			auto animator = make_shared<Animator>();
			monster->AddComponent(animator);
			auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(monster);
	}




	return scene;
}
