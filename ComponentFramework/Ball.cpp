#include "Ball.h"
#include "Texture.h"
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

    this->AddComponent<SDLTexture>(sprite);
    this->AddComponent<Body>(body);

    this->GetComponent<Body>()->OnCreate();

   
    source.x = 0;
    source.y = 0;
    source.w = 60;
    source.h = 60;

    dst.x = 640;
    dst.y = 360;
    dst.h = source.h;
    dst.w = source.w;

    this->GetComponent<SDLTexture>()->OnCreate();
    this->GetComponent <SDLTexture>()->SetRects(source, dst);
    this->GetComponent<SDLTexture>()->LoadImage("Assets/PurpleBall.png");

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
   
}
