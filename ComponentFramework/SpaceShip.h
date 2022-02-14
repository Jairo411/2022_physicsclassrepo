#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <SDL_rect.h>
#include "Actor.h"
#include "Physics.h"
#include "Component.h"
#include "Matrix.h"

/*
 * The SpaceShip class, is my specified gameObject
 */
class Texture;
class SDLTexture;
class Body;
class Physics;
class SpaceShip :public Actor
{
public:
	SpaceShip(Component* parent_);
	virtual ~SpaceShip();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() ;
private:
	SDL_Rect dst;
	SDL_Rect source;
	MATH::Matrix3 WorldPositon;
};
#endif // !SPACESHIP_H
