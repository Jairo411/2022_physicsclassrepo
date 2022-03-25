#include "Scene3.h"

Scene3::Scene3() 
{
	ball = nullptr;
	wall = nullptr;
} 

Scene3::~Scene3()
{
}

bool Scene3::OnCreate()
{
	ball = new Ball(nullptr);
	wall = new Wall(nullptr);
	ball->OnCreate();
	wall->OnCreate();

	

	world->AddGameObjects(ball);
	world->AddGameObjects(wall);
	return true;
}

void Scene3::OnDestroy()
{
}

void Scene3::Update(const float deltaTime_)
{
	ball->Update(deltaTime_);
	wall->Update(deltaTime_);
	//world->Update(deltaTime_);
}

void Scene3::Render()
{
	ball->Render();
	wall->Render();
	//world->Render();
}

void Scene3::HandleEvents(const SDL_Event& sdlEvent_)
{
	
}
