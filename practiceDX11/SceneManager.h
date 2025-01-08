#pragma once

class Scene;

class SceneManager
{
public:

	SceneManager(std::shared_ptr<Graphics> graphics);
	void Init();
	void Update();

	void LoadScene(std::wstring sceneName);
	
		
	std::shared_ptr<Scene>GetActiveScene() { return _activeScene; }

private:
	std::shared_ptr<Scene> LoadTestScene();
private:
	std::shared_ptr<Graphics> _graphics;
private:
	std::shared_ptr<Scene> _activeScene;



};

