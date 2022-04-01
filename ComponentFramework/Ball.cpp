#include "Ball.h"
#include "Texture.h"
#include "Physics.h"
Ball::Ball(Component* component_) : Actor(nullptr), dst(SDL_Rect()), source(SDL_Rect())
{
}

Ball::~Ball()
{
}

bool Ball::OnCreate()
{
    SDLTexture* sprite = nullptr;
    Body* body = nullptr;
    Physics* physics = nullptr;

    

    this->AddComponent<SDLTexture>(sprite);
    this->AddComponent<Body>(body);
    this->AddComponent<Physics>(physics);

    this->GetComponent<Body>()->OnCreate();
    
   
    source.x = 0;
    source.y = 0;
    source.w = 60;
    source.h = 60;

    modelM[0] = source.w;
    modelM[5] = source.h; 

    dst.x = 0;
    dst.y = 0;
    dst.h = source.h;
    dst.w = source.w;

    this->GetComponent<SDLTexture>()->OnCreate();
    this->GetComponent <SDLTexture>()->SetRects(&source, &dst);
    this->GetComponent<SDLTexture>()->LoadImage("Assets/PurpleBall.png");

    this->GetComponent<Body>()->SetVelocity(MATH::Vec3(100.0f, 0.0f, 0.0f));
    this->GetComponent<Body>()->SetRadius(20.0f);
    this->GetComponent<Body>()->SetPosition(MATH::Vec3(dst.x, dst.y, 0.0f));
    return true;
}

void Ball::OnDestroy()
{
    this->GetComponent<SDLTexture>()->~SDLTexture();
}

void Ball::Render()
{
    this->GetComponent<SDLTexture>()->Render();
}

void Ball::Update(const float deltaTime_)
{

    this->GetComponent<Body>()->Update(deltaTime_);
    this->GetComponent<SDLTexture>()->Update(deltaTime_);
    
    MATH::Vec2 positionUpdate = MATH::Vec2();
    positionUpdate.x = this->GetComponent<Body>()->GetVelocity().x * deltaTime_;
    positionUpdate.y = this->GetComponent<Body>()->GetVelocity().y * deltaTime_;

    modelM[12] += positionUpdate.x;
    modelM[13] += positionUpdate.y;


    this->GetComponent<Body>()->SetPosition(MATH::Vec3(modelM[12], modelM[13], 0.0f));
    //New way of updating gameObject Positions
    if (dst.w!=modelM[0])
    {
        dst.w = modelM[0];
        modelM[0] = dst.w;
    }
    else if (dst.h!=modelM[5])
    {
        dst.h = modelM[5];
        modelM[5] = dst.h;
    }
    dst.x = modelM[12];
    dst.y = modelM[13];

}
