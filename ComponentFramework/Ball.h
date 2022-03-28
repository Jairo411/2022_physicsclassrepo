#ifndef BALL_H
#define BALL_H
#include "Actor.h"
#include "Body.h"
#include "Matrix.h"
#include "MMath.h"
#include <SDL_rect.h>
class SDLTexture;
class Ball : public Actor
{
public:
	Ball(Component* parent_);
	~Ball();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Render();
	virtual void Update(const float deltaTime_);
	MATH::Matrix4 modelM;
private:
	SDL_Rect dst;
	SDL_Rect source;
};
#endif
