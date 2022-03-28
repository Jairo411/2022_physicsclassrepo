#ifndef WALL_H
#define WALL_H
#include <SDL_rect.h>
#include "Actor.h"
#include "Plane.h"
#include "Body.h"
#include "Matrix.h"
#include "Vector.h"
class SDLTexture;
class Wall : public Actor
{
public:
	Wall(Component* parent_);
	virtual ~Wall();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	Plane GetPlane();
	MATH::Matrix4 modelM;
	MATH::Matrix4 rotationM;
	SDL_Rect dst;
	float angle;
private:
	Plane plane;
	SDL_Rect source;
};
#endif // !WALL_H
