#include "SpaceShip.h"
#include "Body.h"
#include "Actor.h"
#include "Texture.h"

SpaceShip::SpaceShip(Component* parent_): Actor(nullptr), dst(SDL_Rect()), source(SDL_Rect()), position(MATH::Matrix4())
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
    source.w =  577;
    source.h =  529;
    dst.x = 0;
    dst.y = 0;
    dst.w = 70;
    dst.h = 70;
    int centreXpivot = dst.w / 2;
    int centreYpivot = dst.h / 2;
    position = MATH::Matrix4();
    position[12] = 640; // this is  screen coordinates 
    position[13] = 360; // this is screen coordinates 
    //add components to my spaceShip object

    SDLTexture* sprite = nullptr;
    Body* body = nullptr;
    Physics* physics = nullptr;


    this->AddComponent<SDLTexture>(sprite);
    this->AddComponent<Body>(body);
    this->AddComponent<Physics>(physics);

    this->GetComponent<SDLTexture>()->OnCreate();
    this->GetComponent<SDLTexture>()->SetRects(&source, &dst);
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
    //take from this for data
    position[12] = this->GetComponent<Body>()->GetPosition().x;
    position[13] = this->GetComponent<Body>()->GetPosition().y;

    MATH::Vec2 drawCoords = MATH::Vec2();
    drawCoords.x = position[12] + leftover.x;
    drawCoords.y = position[13] + leftover.y;
    dst.x = drawCoords.x;
    dst.y = drawCoords.y;
    this->GetComponent<SDLTexture>()->SetDisplay(&dst);
}

void SpaceShip::Render() 
{
  this->GetComponent<SDLTexture>()->Render();
}
void SpaceShip::setLeftOver(MATH::Vec3 leftoverAmount_)
{
   leftover = leftoverAmount_;
}
MATH::Vec3 SpaceShip::getPosition()
{
    MATH::Vec3 pos = MATH::Vec3();
    pos.x = position[12];
    pos.y = position[13];
    return pos;
}
