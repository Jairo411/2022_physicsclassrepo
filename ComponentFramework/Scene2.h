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
	void ApplyTorque(float deltatime_);// Just some helper functions
	void ApplyForce(float deltatime_);// Just some helper functions
	/// This update function only holds the simulateEvents
	void SimulationEventUpdate(float deltaTime_);
private:
	SpaceShip* spaceShip;
	Body* Bodyref;
	std::ofstream excelFile;
	MATH::Vec2 converted;
	float totalTime; 
	float currentTicks;
	float prevTicks;
};

#endif