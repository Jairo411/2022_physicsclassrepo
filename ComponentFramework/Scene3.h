#ifndef SCENE3_H
#define SCENE3_H
#include "Scene.h"
#include "Ball.h"
#include "Wall.h"
class Scene3 : public Scene
{
public:
	Scene3();
	~Scene3();
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render();
	virtual void HandleEvents(const SDL_Event& sdlEvent_) override;
private:
	Ball* ball; 
	Wall* wall;
};
#endif // !SCENE3_H

