#include <SDL_events.h>
#include "Scene2.h"
#include "SpaceShip.h"
#include "Actor.h"

Scene2::Scene2()
{
    excelFile = std::ofstream();
    fileName = "DataFile.csv";
    force = MATH::Vec3();
    timeaccumulator = 0.0f;
    spaceShip = new SpaceShip(nullptr);
    leftEngineOff = false;
    rightEngineOff = false;
    started = false;
    ended = false;
}
Scene2::~Scene2()
{
}
bool Scene2::OnCreate()
{
    spaceShip->OnCreate();
    

    MATH::Vec3 spawn = MATH::Vec3();
    spawn.set(640.0f, 360.0f, 0.0f);
    spaceShip->GetComponent<Body>()->SetPosition(spawn);
    Bodyref = spaceShip->GetComponent<Body>();

    force.set(5.0f * powf(10.0f, 7.0f), 0.0f, 0.0f);
    torque = 0.0f;

    excelFile.open(fileName, std::ios::app);
    excelFile << "Time: " << "\t" << "Torque" << "\t" << "AngAccel" << "\t" << "AngVel" << "\t"  << "Angle" 
              << "\t" << "Force.x" << "\t" << "Force.y" << "\t" << "Accel.x" << "\t" << "Accel.y"
              << "\t"<< "Vel.x" << "\t" << "Vel.y" << "\t" << "Pos.x"<< "\t" << "Pos.y" << std::endl;
    return true;
}

void Scene2::OnDestroy()
{
   
}

void Scene2::Update(const float deltaTime)
{ 
    if (ended == false)
    {


        float SecondDelta = floor(secondFlag);
        float TotalTime = floor(timeaccumulator);

        if (SecondDelta == 1.0f) //here is your "ticks"
        {
            TotalTime -= 1;
            if (started == false)
            {
                SecondDelta = 0.0f;
                started = true;
            }
            float changeInTime = TotalTime - TotalTime + SecondDelta;


            if (TotalTime == 5.0f && leftEngineOff == false) //Left engine fails
            {
                force /= 2;
                torque = 6.291 * powf(10, 8);
                leftEngineOff = true;

            }
            else if (TotalTime == 30.0f) // Both engins are turned off
            {
                rightEngineOff = true;
            }
            else if (TotalTime == 60.0f) // End Simulation
            {
                excelFile.close();
                ended = true;
                std::cout << "Simulation ended" << std::endl;
            }

            if (leftEngineOff == true)
            {
                spaceShip->GetComponent<Physics>()->ApplyTorque(torque, changeInTime, spaceShip->GetComponent<Body>());
            }

            if (leftEngineOff && rightEngineOff == true)
            {
                force = MATH::Vec3();
                torque = 0.0f;
                std::cout << "BOTH ENGINES ARE OFF" << std::endl;
                std::cout << "BOTH ENGINES ARE OFF" << std::endl;
                std::cout << "BOTH ENGINES ARE OFF" << std::endl;
            }

            spaceShip->GetComponent<Physics>()->ApplyForce(force, changeInTime, spaceShip->GetComponent<Body>());


            MATH::Vec2 position = MATH::Vec2();
            MATH::Vec2 converted = MATH::Vec2();
            position.set(Bodyref->GetPosition().x, Bodyref->GetPosition().y);



            converted = camera.getWorldPosition(position);

            excelFile << TotalTime << "\t" << torque << "\t" << Bodyref->GetAngularAcceleration() << "\t" << Bodyref->GetAngularVelocity() << "\t" <<

                Bodyref->GetAngularPosition() << "\t" << spaceShip->GetComponent<Body>()->GetForce().x << "\t" << spaceShip->GetComponent<Body>()->GetForce().y << "\t" << Bodyref->GetAcceleration().x << "\t" <<

                Bodyref->GetAcceleration().y << "\t" << Bodyref->GetVelocity().x << "\t" << Bodyref->GetVelocity().y << "\t" <<

                converted.x << "\t" << converted.y << "\t" << std::endl;


            //DEBUG

            std::cout << "Time:" << TotalTime << "\n" << "Torque:" << torque << "\n" << "AngAccel:" << Bodyref->GetAngularAcceleration() << "\n" << "AngVelo:" << Bodyref->GetAngularVelocity()

                << "\n" << "angle:" << Bodyref->GetAngularPosition() << "\n" << "forcex:" << spaceShip->GetComponent<Body>()->GetForce().x << "\n" << "forcey:" << spaceShip->GetComponent<Body>()->GetForce().y << "\n" << "accel.x" << Bodyref->GetAcceleration().x <<

                "\n" << "accel.y:" << Bodyref->GetAcceleration().y << "\n" << "velocityx:" << Bodyref->GetVelocity().x << "\n" << "velocityy:" << Bodyref->GetVelocity().y << "\n"

                << "Posx:" << converted.x << "\n" << "Posy:" << converted.y << std::endl;
            //DEBUG





            secondFlag = 0.0f;
        }

        camera.SetFollowPosition(spaceShip->GetComponent<Body>()->GetPosition());
        camera.Update(deltaTime);
        spaceShip->Update(deltaTime);


        secondFlag += deltaTime;
        timeaccumulator += deltaTime;
    }
  
}

void Scene2::Render() 
{
    spaceShip->Render();
}

void Scene2::HandleEvents(const SDL_Event& sdlEvent)
{
    
    if (sdlEvent.type==SDL_QUIT)
    {
        excelFile.close();
    }
    
}

