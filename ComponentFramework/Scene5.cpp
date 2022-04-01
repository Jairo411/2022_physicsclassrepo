#include "Scene5.h"
#include "Texture.h"
Scene5::Scene5()
{
	ball0 = nullptr;
	ball1 = nullptr;
	lock = false;
}

Scene5::~Scene5()
{
}

bool Scene5::OnCreate()
{
	ball0 = new Ball(nullptr);
	ball1 = new Ball(nullptr);

	ball0->OnCreate();
	ball1->OnCreate();

	world->AddGameObjects(ball0);
	world->AddGameObjects(ball1);

	///MATH for the first ball
	MATH::Matrix4 Mclip = camera->ViewM * ball0->modelM;
	MATH::Vec3 vClip = MATH::Vec3();

	vClip.x = Mclip[12];
	vClip.y = Mclip[13];

	ball0->modelM[12] += vClip.x;
	ball0->modelM[13] += vClip.y;

	///MATH for the second ball 
	MATH::Matrix4 Mclip1 = camera->ViewM * ball1->modelM;
	MATH::Vec3 vClip1 = MATH::Vec3();

	vClip1.x = Mclip1[12];
	vClip1.y = Mclip1[13];

	ball1->modelM[12] += vClip1.x;
	ball1->modelM[13] += vClip1.y;

	SDL_Rect source = SDL_Rect();

	source.x = 0;
	source.y = 0;
	source.h = 70;
	source.w = 70;
	ball0->GetComponent<SDLTexture>()->SetSource(&source);
	ball1->GetComponent<SDLTexture>()->SetSource(&source);
	///Intializing behaviour  
	ball0->GetComponent<Body>()->SetRadius(30.0f);
	ball1->GetComponent<Body>()->SetRadius(30.0f);

	ball0->GetComponent<Body>()->SetMass(1.0f);
	ball1->GetComponent<Body>()->SetMass(1.0f);


	ball0->GetComponent<Body>()->SetVelocity(MATH::Vec3(0.0f, 40.0f, 0.0f));
	ball1->GetComponent<Body>()->SetVelocity(MATH::Vec3(0.0f, 0.0f, 0.0f));
	
	ball0->modelM[13] += -200.0f;


	return true;
}

void Scene5::OnDestroy()
{
}

void Scene5::Update(const float deltaTime_)
{
	Body* sphere0 = ball0->GetComponent<Body>();
	Body* sphere1 = ball1->GetComponent<Body>();
	Physics* physic = ball0->GetComponent<Physics>();
	world->Update(deltaTime_);
	if (physic->SphereToSphereCollisionDetection(*sphere0,*sphere1)&& lock ==false)
	{
		if (lock==false)
		{
			physic->SphereToSphereCollisionResponse(*sphere0, *sphere1);
			lock = true;
		}
	}
}

void Scene5::Render()
{
	world->Render();
}

void Scene5::HandleEvents(const SDL_Event& sdlEvent_)
{
}
