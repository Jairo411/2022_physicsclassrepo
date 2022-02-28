#ifndef	WORLD_H
#define WORLD_H
#include "Matrix.h"
#include "Component.h"
#include "Camera.h"
#include "Actor.h"
#include <vector>
/*Window is programmed to create its own default camera, don't script anything else in terms of intializing the camera*/
class World
{
public:
	World(const World&) = delete;
	World(World&&) = delete;
	World& operator=(const World&) = delete;
	World& operator=(World&&) = delete;

	World();
	~World();
	///Input half of the Screen size in order to set the origin in the middle of the screen 
	void OnCreate(const int startPosx_, const int startPosy_);
	void OnDestroy();
	void Update(float deltaTime_);
	void Render();
	void AddGameObjects(Actor* OBJ_);
	void UpdateCamera(Camera* camera_,float deltaTime_);
	MATH::Vec3 getPosition(MATH::Vec3 position_);
private:
	MATH::Matrix4 WorldOrigin; // world starts at the centre of the screen 
	std::vector<Actor*> Objects;
};
#endif
