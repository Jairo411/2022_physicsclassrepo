#include "Scene3.h"

Scene3::Scene3() 
{
	ball = nullptr;
	wall = nullptr;
} 

Scene3::~Scene3()
{
}

bool Scene3::OnCreate()
{
	ball = new Ball(nullptr);
	ball1 = new Ball(nullptr);
	wall = new Wall(nullptr);


	ball->OnCreate();
	ball1->OnCreate();
	wall->OnCreate();

	world->AddGameObjects(ball);
	world->AddGameObjects(ball1);
	world->AddGameObjects(wall);
	///Right now, this isn't the full Vclip = MProjection * Mview * Model * vlocal
	///But we are getting their.
	///Matrix Math  for the wall
	MATH::Matrix4 Mclip = camera->ViewM * wall->modelM;
	MATH::Vec3 vClip = MATH::Vec3();
	wall->angle = 45.0f;
	vClip.x = Mclip[12];
	vClip.y = Mclip[13];

	wall->modelM[12] += vClip.x;
	wall->modelM[13] += vClip.y;

	///Matrix Math for the ball
	MATH::Matrix4 Mclip0 = camera->ViewM * ball->modelM;
	MATH::Vec3 vClip0 = MATH::Vec3();
	vClip0.x = Mclip0[12];
	vClip0.y = Mclip0[13];
	ball->modelM[12] += vClip0.x;
	ball->modelM[13] += vClip0.y;

	///Matrix Math for the second ball
	MATH::Matrix4 Mclip1 = camera->ViewM * ball1->modelM;
	MATH::Vec3 vClip1 = MATH::Vec3();
	vClip1.x = Mclip1[12];
	vClip1.y = Mclip1[13];

	ball1->modelM[12] += vClip1.x;
	ball1->modelM[13] += vClip1.y;

	ball1->GetComponent<Body>()->SetVelocity(MATH::Vec3(-100.0f, 0.0f, 0.0f));

	//translations
	ball->modelM[12] += -500.0f;

	//translations
	ball1->modelM[12] += 500.0f;


	Mclip.print();
	Mclip0.print();

	return true;
}

void Scene3::OnDestroy()
{
}

void Scene3::Update(const float deltaTime_)
{
	Body* sphere = ball->GetComponent<Body>();
	Body* sphere1 = ball1->GetComponent<Body>();
	world->Update(deltaTime_);
	ball->GetComponent<Physics>()->SphereToPlaneCollisionDetected(*sphere, wall->GetPlane());
	ball1->GetComponent<Physics>()->SphereToSphereCollisionDetected(*sphere, *sphere1);
//	ball->modelM.print();
}

void Scene3::Render()
{
	world->Render();
}

void Scene3::HandleEvents(const SDL_Event& sdlEvent_)
{
	switch (sdlEvent_.type)
	{
	case SDL_KEYDOWN:
		std::cout << "Wall matrix" << std::endl;
		wall->modelM.print();
		std::cout << "Ball matrix" << std::endl;
		ball->modelM.print();
		break;
	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONDOWN:
		break;

	default:
		break;
	};
}

void Scene3::ComputeBoundingBox(const MATH::Vec3 in, MATH::Vec3 out, const MATH::Matrix4 M)
{
}
