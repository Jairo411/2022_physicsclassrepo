#ifndef SCENE_2H
#define SCENE_2H
#include "Scene.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cstdio>
#include "Body.h"
union SDL_Events;
class SpaceShip;
class Scene2 : public Scene
{
public: 
	Scene2();
	~Scene2();
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render();
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
private:
	SpaceShip* spaceShip;
	Body* Bodyref;
	std::ofstream excelFile;
	MATH::Vec3 force;
	MATH::Vec2 converted;
	float torque;
	float timeaccumulator;
	float secondFlag;
	const char* fileName;
	bool leftEngineOff;
	bool rightEngineOff;
	bool started;
	bool ended;
};

#endif