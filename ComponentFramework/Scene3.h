#ifndef SCENE3_H
#define SCENE3_H
#include "Scene.h"
#include "Ball.h"
#include "Wall.h"
#include "Matrix.h"
#include "Body.h"
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
	void ComputeBoundingBox(const MATH::Vec3 in, MATH::Vec3 out, const MATH::Matrix4 M);
private:
	Ball* ball; 
	Ball* ball1;
	Wall* wall;
	
};
#endif // !SCENE3_H

