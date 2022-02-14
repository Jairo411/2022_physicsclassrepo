#include "SpaceShip.h"
#include "Body.h"
#include "Actor.h"
#include "Texture.h"

SpaceShip::SpaceShip(Component* parent_): Actor(nullptr), dst(SDL_Rect()), source(SDL_Rect())  , WorldPositon(MATH::Matrix3())
{   
}

SpaceShip::~SpaceShip()
{
}

bool SpaceShip::OnCreate() // place where I can hard code my spaceShip class
{
    //setting up SDL images box containers
    source.x = 0;
    source.y = 0;
    source.w = 557;
    source.h = 529;
    dst.x = 0;
    dst.y = 0;
    dst.w = 70;
    dst.h = 70;
    WorldPositon = MATH::Matrix3();
    WorldPositon[6] = 640;
    WorldPositon[7] = 360;
    //add components to my spaceShip object

    SDLTexture* sprite = nullptr;
    Body* body = nullptr;
    Physics* physics = nullptr;


    this->AddComponent<SDLTexture>(sprite);
    this->AddComponent<Body>(body);
    this->AddComponent<Physics>(physics);

    this->GetComponent<SDLTexture>()->OnCreate();
    this->GetComponent<SDLTexture>()->SetRects(source, dst);
    this->GetComponent<SDLTexture>()->LoadImage("Assets/SpaceShip.png");
  
    this->GetComponent<Body>()->OnCreate();
    this->GetComponent<Body>()->SetMass(1.0f * powf(10, 6));
    this->GetComponent<Body>()->SetRotationalInertia(2.67f * powf(10,10));
    this->GetComponent<Physics>()->OnCreate();

    

      return true;

}

void SpaceShip::OnDestroy()
{
}

void SpaceShip::Update(const float deltaTime_)
{
    dst.x = this->GetComponent<Body>()->GetPosition().x;
    dst.y = this->GetComponent<Body>()->GetPosition().y;
    this->GetComponent<SDLTexture>()->SetDisplay(dst);
}

void SpaceShip::Render() 
{
  this->GetComponent<SDLTexture>()->Render();
}
