#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>
#include "Camera.h"
/* REMEMBER THAT YOU NEED TO CHANGE THE OPENGL FLAG AS WELL AS THE SCENE
* To keep things from not breaking.
*/
class SceneManager  {
public:
	
	SceneManager();
	~SceneManager();
	void Run();
	bool Initialize(std::string name_, int width_, int height_);
	void HandleEvents();
private:
	enum class SCENE_NUMBER {
		SCENE0 = 0,
		SCENE1,
		SCENE2,
		SCENE3,
		SCENE4,
		SCENE5,
		SCENE6
	};
	class Scene* currentScene;
	class Timer* timer;
	class Window* window;
	class World* world;
	SCENE_NUMBER sceneID;
	unsigned int fps;
	bool isRunning;
	bool fullScreen;
	bool isOpenGL;
	
	void BuildNewScene(SCENE_NUMBER scene_);
};


#endif // SCENEMANAGER_H