#include "Wall.h"
#include "Texture.h"

Wall::Wall(Component* parent_) : Actor(nullptr), plane(Plane()) , dst(SDL_Rect()) , source(SDL_Rect())
{
}

Wall::~Wall()
{
}

bool Wall::OnCreate()
{

    SDLTexture* sprite = nullptr;
    Body* body = nullptr;
    

    this->AddComponent<SDLTexture>(sprite);
    this->AddComponent<Body>(body);

    this->GetComponent<SDLTexture>()->OnCreate();
    this->GetComponent<Body>()->OnCreate();
   
    /* 
    * Alright after 3ish something years, you now finally know how coordinate systems 
    * essentally work. Since I'm building this or working a my own coordinate systems 
    * frame work ill drop the comments nessary to explain what is in what coordinate system.
    * 
    * First off, when intializing you texture which are your gameObjects, you're in model coordinate system. 
    * Everything you do here is essentially how you create/manipulate your texture before it is printed onto the screen.
    */
    source.x = 0;
    source.y = 0;
    source.w = 60;
    source.h = 190;
    dst.x = 0;
    dst.y = 0;
    dst.w = source.w;
    dst.h = source.h;

   
    this->GetComponent<SDLTexture>()->OnCreate();
    this->GetComponent <SDLTexture>()->SetRects(source, dst);
    this->GetComponent<SDLTexture>()->LoadImage("Assets/Wall.png");

    return false;
}

void Wall::OnDestroy()
{
    this->GetComponent<SDLTexture>()->~SDLTexture();
}

void Wall::Update(const float deltaTime_)
{
    /*Over here in the update you need to do the proper matrix mutliplications in order for your coordinate system to work properly.
    * ModelM*ViewM*ProjectionM 
    * Another Note the only thing that should be in this wall gameObject's memory is ModelM, the other two Matrix can semi-permanently exist in the rendering pipeline
    */
    this->GetComponent<SDLTexture>()->Update(deltaTime_);
}

void Wall::Render()
{
    this->GetComponent<SDLTexture>()->Render();
}
