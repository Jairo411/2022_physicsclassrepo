#include "Scene4.h"
#include "Texture.h"
Scene4::Scene4()
{
	ball0 = nullptr;
	ball1 = nullptr;
}

Scene4::~Scene4()
{
}

bool Scene4::OnCreate()
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

	vClip1.x = Mclip[12];
	vClip1.y = Mclip[13];

	ball1->modelM[12] += vClip1.x;
	ball1->modelM[13] += vClip1.y;

	SDL_Rect source = SDL_Rect();

	source.x = 0;
	source.y = 0;
	source.h = 70;
	source.w = 70;
	ball1->GetComponent<SDLTexture>()->SetSource(&source);
	ball0->GetComponent<SDLTexture>()->SetSource(&source);
	///Intializing behaviour for the first ball
	//move it 3 units to the right
	ball0->modelM[12] += 300.0f;
	//move it 4 units up 
	ball0->modelM[13] += -420.0f;
	ball0->GetComponent<Body>()->SetRadius(30.0f);
	ball0->GetComponent<Body>()->SetVelocity(MATH::Vec3(0.0f,40.0f,0.0f));
	///Intializing behaviour for the second ball
	//move it 2.5 units to the right
	ball1->modelM[12] += 250.0f;
	//move it 2 units down
	ball1->modelM[13] += -200.0f;
	ball1->GetComponent<Body>()->SetRadius(30.0f);
	ball1->GetComponent<Body>()->SetVelocity(MATH::Vec3());

	std::cout << "ball 1" << std::endl;
	ball0->modelM.print();
	std::cout << "ball 2" << std::endl;
	ball1->modelM.print();
	return true;
}

void Scene4::OnDestroy()
{
}

void Scene4::Update(const float deltaTime_)
{
	Body* sphere0 = ball0->GetComponent<Body>();
	Body* sphere1 = ball1->GetComponent<Body>();
	Physics* physic = ball0->GetComponent<Physics>();
	world->Update(deltaTime_);
	if (physic->SphereToSphereCollisionDetection(*sphere0,*sphere1))
	{
		physic->SphereToStaticSphereCollisionResponse(*sphere0, *sphere1);	
	}
	
}

void Scene4::Render()
{
	world->Render();
}

void Scene4::HandleEvents(const SDL_Event& sdlEvent_)
{
	switch (sdlEvent_.type)
	{
	case SDL_KEYDOWN:
	
	case SDL_MOUSEMOTION:

		break;

	case SDL_MOUSEBUTTONDOWN:

		break;
	}
}
