#pragma once
#include <string>
#include "Graphics.h"
#include "GameObject.h"
class Game
{

public:
	Game();
	~Game();

public:
	void init(HWND hwnd);
	void update();
	void Render();

private:
	HWND _hwnd;
	//shared_ptr<Graphics> _graphics;// precompileheader

	std::shared_ptr<Graphics> _graphics;// smart pointer
	std::shared_ptr<Pipeline> _pipeline;
	
	//temp
	std::shared_ptr<GameObject> _monster;// ¿©·¯°³ 
	std::shared_ptr<GameObject> _camera;
};