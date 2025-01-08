#include "stdafx.h"
#include "Game.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"
//class Graphics;



std::unique_ptr<Game>GGame= std::make_unique<Game>();

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(HWND hwnd)
{
	_hwnd = hwnd;
	_graphics = std::make_shared<Graphics>(hwnd);
	//_pipeline = std::make_shared<Pipeline>(_graphics->GetDeviceContext());
	_input = std::make_shared<InputManager>();
	_input->Init(hwnd);
	_time = std::make_shared<TimeManager>();
	_time->Init();
	_scene = std::make_shared<SceneManager>(_graphics);
	_scene->Init();
	_resource = std::make_shared<ResourceManager>(_graphics->GetDevice());
	_resource->Init();
	_render = std::make_shared<RenderManager>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_render->Init();

	SCENE->LoadScene(L"Test");


}

void Game::Update()
{

	TIME->Update();
	INPUT->Update();
	SCENE->Update();
}

void Game::Render()
{
	// 오브젝트 생성
// IA- VS- RS- PS- OM
	 

	RENDER->Update(_graphics);

	//HDC
		//temp
	//_monster->GetMeshRenderer()->Render(_pipeline);




}