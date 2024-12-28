#include "stdafx.h"
#include "Game.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "SceneManager.h"
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
	_pipeline = std::make_shared<Pipeline>(_graphics->GetDeviceContext());

	_monster = std::make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_monster->GetOrAddTransform();
	_monster->AddComponent(std::make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext()));


	_camera = std::make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_camera->GetOrAddTransform();
	_camera->AddComponent(
		std::make_shared<Camera>());

	_scene = std::make_shared<SceneManager>();


	SCENE->LoadScene(L"Test");



}

void Game::update()
{

	_monster->Update();

	_camera->Update();

	SCENE->Update();
}

void Game::Render()
{
	// 오브젝트 생성
// IA- VS- RS- PS- OM
	_graphics->RenderBegin();// 도화지 갱신


	//HDC
		//temp
	_monster->GetMeshRenderer()->Render(_pipeline);

	_graphics->RenderEnd();



}

	//const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	//_graphics->GetDevice()->CreateInputLayout(layout,count,_vsBlob->GetBufferPointer(),_vsBlob->GetBufferSize(),_inputLayout.GetAddressOf());
	//3번째 인자가 쉐이더와 연관이 되어있기 때문에 쉐이더부터 만든다.
	//blob->쉐이더 연관.
	// input layout 
