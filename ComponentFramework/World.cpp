#include "World.h"

World::World()
{
	WorldOrigin = MATH::Vec3();
	objects = std::vector<Actor*>();
}

World::~World()
{
}

void World::OnCreate(Camera* camera_)
{
	WorldOrigin.x = camera_->GetOrigin().x;
	WorldOrigin.y = camera_->GetOrigin().y;
}

void World::OnDestroy()
{

}

void World::Update(float deltaTime_)
{
	for (Actor* obj : objects )
	{
		obj->Update(deltaTime_);
	}
}

void World::Render()
{
	//I could write code like, if obj is out of the screen then don't render it but I won't >:) 
	for (Actor* obj : objects)
	{
		obj->Render();
	}
}

void World::AddGameObjects(Actor* OBJ_)
{
	objects.push_back(OBJ_);
}

void World::UpdateWorld(Camera* camera_)
{
	MATH::Vec3 distanceFromCamera = MATH::Vec3();
	MATH::Vec3 cameraPosition = camera_->GetPosition();
	std::vector<MATH::Vec3> ObjectPositions = std::vector<MATH::Vec3>();
	
	SpaceShip* obj = dynamic_cast<SpaceShip*>(objects[0]);
	MATH::Vec3 objPosition = getPosition(obj->getPosition());

	//This part is suppose to loop over it doesn't but im still coding like it does
	distanceFromCamera = objPosition - cameraPosition;
	ObjectPositions.push_back(distanceFromCamera);
	if (distanceFromCamera.x >400)
	{
		camera_->Translate(MATH::Vec3(1920, 0.0f, 0.0f));
	}
	std::cout << "distance from camera" << distanceFromCamera.x << "," << distanceFromCamera.y << std::endl;
	std::cout << "object Position : " << obj->getPosition().x << "," << obj->getPosition().y << std::endl;
	std::cout << "camera Position :" << camera_->GetPosition().x << "," << camera_->GetPosition().y << std::endl;
	obj->setLeftOver(distanceFromCamera);
	
}


MATH::Vec3 World::getPosition(MATH::Vec3 position_)
{
	MATH::Vec3 convertedPosition = MATH::Vec3();
	convertedPosition.x = position_.x - WorldOrigin.x; //giving the position realtive to the world origin
	convertedPosition.y = WorldOrigin.y - position_.y;
	return convertedPosition;
}


MATH::Vec3 World::getOrigin()
{
	MATH::Vec3 origin = MATH::Vec3();
	origin.x = WorldOrigin.x;
	origin.y = WorldOrigin.y;
	origin.z = 0.0f;
	return origin;
}
