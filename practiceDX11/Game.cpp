#include "stdafx.h"
#include "Game.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
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
	_input = std::make_shared<InputManager>();
	_input->Init(hwnd);
	_time = std::make_shared<TimeManager>();
	_time->Init();


	_scene = std::make_shared<SceneManager>(_graphics);
	_scene->Init();

	SCENE->LoadScene(L"Test");



}

void Game::Update()
{

	//_monster->Update();

	//_camera->Update();
	TIME->Update();
	INPUT->Update();
	SCENE->Update();
}

void Game::Render()
{
	// ������Ʈ ����
// IA- VS- RS- PS- OM
	_graphics->RenderBegin();// ��ȭ�� ����

	SCENE->Update();
	//HDC
		//temp
	//_monster->GetMeshRenderer()->Render(_pipeline);

	_graphics->RenderEnd();



}

	//const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	//_graphics->GetDevice()->CreateInputLayout(layout,count,_vsBlob->GetBufferPointer(),_vsBlob->GetBufferSize(),_inputLayout.GetAddressOf());
	//3��° ���ڰ� ���̴��� ������ �Ǿ��ֱ� ������ ���̴����� �����.
	//blob->���̴� ����.
	// input layout 
