#ifndef SCENE5_H
#define SCENE5_H
#include "Scene.h"
#include "Ball.h"
#include "Body.h"
#include "Matrix.h"
class Scene5 : public Scene
{
public:
	Scene5();
	~Scene5();
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render();
	virtual void HandleEvents(const SDL_Event& sdlEvent_) override;
private:
	Ball* ball0;
	Ball* ball1;
	bool lock;
};

#endif // !SCENE5_H

