#include "World.h"

World::World()
{
	WorldOrigin = MATH::Matrix4();
	Objects = std::vector<Actor*>();
}

World::~World()
{
}

void World::OnCreate(const int startPosx_, const int startPosy_)
{
	WorldOrigin[12] = startPosx_/2;
	WorldOrigin[13] = startPosy_/2;
}

void World::OnDestroy()
{

}

void World::Update(float deltaTime_)
{
	for (Actor* obj : Objects )
	{
		obj->Update(deltaTime_);
	}
}

void World::Render()
{
	//I could write code like, if obj is out of the screen then don't render it but I won't >:) 
	for (Actor* obj : Objects)
	{
		obj->Render();
	}
}

void World::AddGameObjects(Actor* OBJ_)
{
	Objects.push_back(OBJ_);
}

void World::UpdateCamera(Camera* camera_, float deltaTime_)
{
	MATH::Vec3 cameraPosition = MATH::Vec3();
	MATH::Vec3 Position = MATH::Vec3();
	MATH::Vec3 distanceFromCamera = MATH::Vec3();
	std::vector<MATH::Vec3> objectPositions = std::vector<MATH::Vec3>();

	cameraPosition.set(camera_->getPosition().x, camera_->getPosition().y,0.0f);
	
	for (int i = 0; i < Objects.size(); i++)
	{
			
	}

}


MATH::Vec3 World::getPosition(MATH::Vec3 position_)
{
	MATH::Vec3 convertedPosition = MATH::Vec3();
	convertedPosition.x = position_.x - WorldOrigin[12]; //giving the position realtive to the world origin
	convertedPosition.y = WorldOrigin[13] - position_.y;
	return convertedPosition;
}
