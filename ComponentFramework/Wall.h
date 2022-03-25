#ifndef WALL_H
#define WALL_H
#include <SDL_rect.h>
#include "Actor.h"
#include "Plane.h"
#include "Body.h"
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
private:
	Plane plane;
	SDL_Rect dst;
	SDL_Rect source;
};
#endif // !WALL_H
