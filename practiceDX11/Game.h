#pragma once
#include <string>
#include "Graphics.h"
#include "GameObject.h"
#include "Pipeline.h"	


class SceneManager;
class InputManager;
class TimeManager;
class ResourceManager;
class RenderManager;

class Game
{

public:
	Game();
	~Game();

public:
	void init(HWND hwnd);
	void Update();
	void Render();

	std::shared_ptr<SceneManager> GetSceneManager() { return _scene; }
	std::shared_ptr<TimeManager> GetTimeManager() { return _time; }
	std::shared_ptr<InputManager> GetInputManager() { return _input; }
	std::shared_ptr<ResourceManager> GetResourceManager() { return _resource; }
	std::shared_ptr<RenderManager> GetRenderManager() { return _render; }


	
private:
	HWND _hwnd;
	//shared_ptr<Graphics> _graphics;// precompileheader

	std::shared_ptr<Graphics> _graphics;// smart pointer
	//std::shared_ptr<Pipeline> _pipeline;
	
	//temp
	std::shared_ptr<GameObject> _monster;// ������ 
	std::shared_ptr<GameObject> _camera;

	std::shared_ptr<SceneManager> _scene;
	std::shared_ptr<TimeManager> _time;
	std::shared_ptr<InputManager> _input;

	std::shared_ptr<ResourceManager> _resource;
	std::shared_ptr<RenderManager> _render;
};
extern std::unique_ptr<Game> GGame;