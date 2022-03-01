#ifndef	WORLD_H
#define WORLD_H
#include "Matrix.h"
#include "Component.h"
#include "Camera.h"
#include "Actor.h"
#include "Body.h"
#include "SpaceShip.h"
#include <vector>
/*Window is programmed to create its own default camera, don't script anything else in terms of intializing the camera*/
/* so note with the world class certain features should be static, the gameobjects are tied to the world.*/
class World
{
public:
	World(const World&) = delete;
	World(World&&) = delete;
	World& operator=(const World&) = delete;
	World& operator=(World&&) = delete;

	World();
	~World();
	///Pass the camera to the world since the camera coordinate system and the world coordinate system 
	///are the similar 
	void OnCreate(Camera* camera_);
	void OnDestroy();
	void Update(float deltaTime_);
	void Render();
	void AddGameObjects(Actor* OBJ_);
	//Get Objects positions realtive to the camera
	void UpdateWorld(Camera* camera_);
	MATH::Vec3 getPosition(MATH::Vec3 position_);
	[[deprecated("just returns the screencoordinates of the world class origin, don't use it")]]
	MATH::Vec3 getOrigin();	
private:
	MATH::Vec3 WorldOrigin; // World origin data is screen coordinates
	std::vector<Actor*> objects;
};
#endif
