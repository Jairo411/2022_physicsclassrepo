#include "Wall.h"
#include "Texture.h"

Wall::Wall(Component* parent_) : Actor(nullptr), plane(Plane()) , dst(SDL_Rect()) , source(SDL_Rect()), angle(0.0f)
{
}

Wall::~Wall()
{
}

bool Wall::OnCreate()
{

    SDLTexture* sprite = nullptr;
    Body* body = nullptr;
    plane = Plane(-1.0f, 1.0f, 0.0f, 0.0f);
    

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
    * 2022-03-25
    */
    source.x = 0;
    source.y = 0;
    source.w = 60;
    source.h = 190;

    modelM[0] = source.w;
    modelM[5] = source.h;
    
    angle = 0;

    rotationM[0] = angle;
    rotationM[4] = angle;

    dst.x = 0;
    dst.y = 0;
    dst.w = source.w;
    dst.h = source.h;
   
    this->GetComponent<Body>()->SetPosition(MATH::Vec3(dst.x,dst.y,0.0f));
   


    /* Okay so over here, when we create our texture, lets imagine that our we're working in local coordinates. 
    *  We're creating our texture or gameObject whatever it is.
    * 2022-03-26
    */
    this->GetComponent<SDLTexture>()->OnCreate();
    this->GetComponent<SDLTexture>()->SetRects(&source, &dst);
    this->GetComponent<SDLTexture>()->SetAngle(&angle);
    this->GetComponent<SDLTexture>()->LoadImage("Assets/Wall.png");


    angle = cosf(angle);
    return false;
}

void Wall::OnDestroy()
{
    this->GetComponent<SDLTexture>()->~SDLTexture();
}

void Wall::Update(const float deltaTime_)
{
    /*Over here in the update you need to do the proper matrix mutliplications in order for your coordinate system to work properly.
    * VClip = ProjectionM*ViewM*ModelM
    * Another Note the only thing that should be in this wall gameObject's memory is ModelM, the other two Matrix can semi-permanently exist in the rendering pipeline
    * 2022-03-25
    */
    /*
    * So in SDL the only way to "translate" our object is to change the display rect in the rendercopy function.
    * Since I added the Model Matrix, we will be able to contain data relavent to our gameObject.
    * After adding this model matrix, I currently thinking about how unity applys their translate functions to their 
    * game objects in code, I currently believe that I can set this up in some sort as well. 
    * 2022-03-26
    */
    //If the past angle doesn't equal the current angle then update the angle of matrix
    //do matrix math as well.
    // I can test this with a simple caluclation of costheta
    //Overhere we're assuming that the matrix is contain the angle in degrees
    //if (angle!= rotationM[0]) //write a sort explaination 
    //{
    //    //Then convert 
    //    float cosA = cosf(angle);
    //    float sinA = sinf(angle+0.1);
    //    rotationM[0] = cosA;
    //    rotationM[4] = sinA * -1;
    //    rotationM[1] = sinA * -1;
    //    rotationM[5] = cosA;
    //    angle = cosA;
    //    
    //    MATH::Vec2 PolarCoordinates = MATH::Vec2();

    //    PolarCoordinates.x = modelM[12] * rotationM[0] + modelM[13] * rotationM[4];
    //    PolarCoordinates.y = modelM[12] * rotationM[1] + modelM[13] * rotationM[5];

    //    modelM[12] = PolarCoordinates.x;
    //    modelM[13] = PolarCoordinates.y;
    //}

    this->GetComponent<Body>()->SetPosition(MATH::Vec3(modelM[12], modelM[13], 0.0f));
    plane.SetPosition(this->GetComponent<Body>()->GetPosition());
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
    this->GetComponent<SDLTexture>()->Update(deltaTime_);
}

void Wall::Render()
{
    this->GetComponent<SDLTexture>()->RenderEx();
}

Plane Wall::GetPlane()
{
    return plane;
}

