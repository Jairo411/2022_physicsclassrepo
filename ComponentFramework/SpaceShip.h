#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <SDL_rect.h>
#include "Actor.h"
#include "Physics.h"
#include "Component.h"
#include "Matrix.h"

/*
 * The SpaceShip class, is my specified gameObject
 * SDLTexture, Body, Physics are coded into the SpaceShip class 
 * because I wanted to test for it, other than that you can add these objects 
 * in a composition type manner.
 */
/* GameObject classes should really only have the functionality of changing movement and seeing what they have. 
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
	virtual void Render();
	MATH::Vec3 getPosition();
	void setLeftOver(MATH::Vec3 leftoverAmount_);
private:
	//Display represents, where on the screen the image is 
	SDL_Rect dst;
	SDL_Rect source;
	//the position should be modifyable not the display rect
	MATH::Vec3 leftover;
	MATH::Matrix4 position;
};
#endif // !SPACESHIP_H
