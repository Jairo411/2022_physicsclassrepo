#include "SceneManager.h"
#include "Timer.h"
#include "Window.h"
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Camera.h"


SceneManager::SceneManager(): 
	currentScene(nullptr), window(nullptr), timer(nullptr),
	fps(60), isRunning(false), fullScreen(false),isOpenGL(false){
	Debug::Info("Starting the SceneManager", __FILE__, __LINE__);
}

SceneManager::~SceneManager() {
	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}
	
	if (timer) {
		delete timer;
		timer = nullptr;
	}

	if (window) {
		delete window;
		window = nullptr;
	}
	Debug::Info("Deleting the SceneManager", __FILE__, __LINE__);
}

bool SceneManager::Initialize(std::string name_, int width_, int height_)
{

	window = new Window();
	bool tempFlag = true;

	if (tempFlag==false)
	{
		isOpenGL = true;
	}
	else if (tempFlag==true)
	{
		isOpenGL = false;
	}

	if (!window->OnCreate(name_, width_, height_,tempFlag)) {
		Debug::FatalError("Failed to initialize Window object", __FILE__, __LINE__);
		return false;
	}
	window->SetCamera(new Camera());
	timer = new Timer();
	if (timer == nullptr) {
		Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
		return false;
	}

	/********************************   Default first scene   ***********************/
	BuildNewScene(SCENE_NUMBER::SCENE3);
	
	return true;
}

/// This is the whole game
void SceneManager::Run() {
	timer->Start();
	isRunning = true;
	if (isOpenGL == true)
	{
		while (isRunning) {
			timer->UpdateFrameTicks();
			currentScene->Update(timer->GetDeltaTime());
			currentScene->Render();
			HandleEvents();
			SDL_GL_SwapWindow(window->getWindow());
			SDL_Delay(timer->GetSleepTime(fps));
		}
	}
	else  if(isOpenGL==false) ///Using the SDL renderer here 
	{
		while (isRunning)
		{
			SDL_RenderClear(window->getRenderer());
			timer->UpdateFrameTicks();
			currentScene->Update(timer->GetDeltaTime());
			currentScene->Render();
			HandleEvents();
			SDL_RenderPresent(window->getRenderer());
		}
	}
}

void SceneManager::HandleEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
			isRunning = false;
		}
		else if (sdlEvent.type == SDL_KEYDOWN) {
			switch (sdlEvent.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
			case SDL_SCANCODE_Q:
				isRunning = false;
				return;
				[[fallthrough]]; /// C17 Prevents switch/case fallthrough warnings
			default:
				break;
			}
		}
		if (currentScene == nullptr) {
			Debug::FatalError("Failed to initialize Scene", __FILE__, __LINE__);
			isRunning = false;
			return;
		}
		currentScene->HandleEvents(sdlEvent);
	}
}

void SceneManager::BuildNewScene(SCENE_NUMBER scene) {
	bool status; 
	if (currentScene != nullptr) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}
	switch (scene) {
	case SCENE_NUMBER::SCENE0:
		currentScene = new Scene0();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE1:
		currentScene = new Scene1();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE2:
		world = new World();
		world->OnCreate(window->GetCamera());
		currentScene = new Scene2();
		currentScene->SetCamera(window->GetCamera());
		currentScene->SetWorld(world);
		status = currentScene->OnCreate();
		break;
	case SCENE_NUMBER::SCENE3:
		world = new World();
		world->OnCreate(window->GetCamera());
		currentScene = new Scene3();
		currentScene->SetCamera(window->GetCamera());
		currentScene->SetWorld(world);
		status = currentScene->OnCreate();
		break;
	default:
		Debug::Error("Incorrect scene number assigned in the manager", __FILE__, __LINE__);
		currentScene = nullptr;
		world = nullptr;
		break;
	}	
}


