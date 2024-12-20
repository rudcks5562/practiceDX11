#include "stdafx.h"
#include "Game.h"


//class Graphics;

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

	_gameObject = std::make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	//GO


}

void Game::update()
{

	_gameObject->Update();
}

void Game::Render()
{
	// ������Ʈ ����
// IA- VS- RS- PS- OM
	_graphics->RenderBegin();// ��ȭ�� ����


	//HDC
	_gameObject->Render(_pipeline);

	_graphics->RenderEnd();



}

	//const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	//_graphics->GetDevice()->CreateInputLayout(layout,count,_vsBlob->GetBufferPointer(),_vsBlob->GetBufferSize(),_inputLayout.GetAddressOf());
	//3��° ���ڰ� ���̴��� ������ �Ǿ��ֱ� ������ ���̴����� �����.
	//blob->���̴� ����.
	// input layout 
