#ifndef SCENE_H
#define SCENE_H
#include "Component.h"
#include "Camera.h"
#include "World.h"
union SDL_Event;
class Scene : public Component {
public:	
	Scene(): Component(nullptr) , camera(nullptr), world(nullptr) {} 
	virtual ~Scene() {}
	/// These are not nessesary since they were already defined in Component.h
	/***
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const  = 0 ;
	***/
	virtual void HandleEvents(const SDL_Event& sdlEvent) = 0;
	void SetCamera(Camera* camera_)
	{
		camera = camera_;
	};
	void SetWorld(World* world_)
	{
		world = world_;
	};
protected:
	Camera* camera;
	World* world;
};
#endif