#ifndef SCENE4_H
#define SCENE4_H
#include "Scene.h"
#include "Ball.h"
#include "Body.h"
#include "Matrix.h"

class Scene4 : public Scene
{
public:
	Scene4();
	~Scene4();
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render();
	virtual void HandleEvents(const SDL_Event& sdlEvent_) override;
private:
	Ball* ball0;
	Ball* ball1;
};
#endif
