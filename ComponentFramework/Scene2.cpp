#include <SDL_events.h>
#include "Scene2.h"
#include "SpaceShip.h"
#include "Actor.h"

Scene2::Scene2()
{
    excelFile = std::ofstream();
    totalTime = 0.0f;
    currentTicks = 0.0f;
    prevTicks = 0.0f;
    spaceShip = new SpaceShip(nullptr);
}
Scene2::~Scene2()
{
}
bool Scene2::OnCreate()
{
    spaceShip->OnCreate();
    
    world->AddGameObjects(dynamic_cast<Actor*>(spaceShip));
    MATH::Vec3 spawn = MATH::Vec3();
    MATH::Vec3 force = MATH::Vec3();
    force.set(5.0f * powf(10.0f, 7.0f), 0.0f, 0.0f);
    spawn.set(640.0f, 360.0f, 0.0f);
    spaceShip->GetComponent<Body>()->SetPosition(spawn);
    spaceShip->GetComponent<Body>()->SetForce(force);
    Bodyref = spaceShip->GetComponent<Body>();
    excelFile.open("DataFile.csv", std::ios::app);
    excelFile << "Time: " << "," << "Torque" << "," << "AngAccel" << "," << "AngVel" << "," << "Angle"
        << "," << "Force.x" << "," << "Force.y" << "," << "Accel.x" << "," << "Accel.y"
        << "," << "Vel.x" << "," << "Vel.y" << "," << "Pos.x" << "," << "Pos.y" << std::endl;
    return true;
}

void Scene2::OnDestroy()
{
   
}

void Scene2::Update(const float deltaTime)
{ 
        /* Ticks is just the unit of time that I am using here,
         *  a tick simply just a second, tick = 1s. It is also
         *  accumlative. Also to keep the updates within a second
         *  I simply compare the currentticks with the last previous ticks,
         * and if the last ticks are no equal, then the condition is met. 
         * The reason it works is because both ticks are updated when a second pass,
         * so therefore the condition will be met every second.
         */
       if (currentTicks != prevTicks||totalTime==0.0f)
       {

           MATH::Vec3 position = MATH::Vec3();
           MATH::Vec3 converted = MATH::Vec3();
           position = Bodyref->GetPosition();
           converted = world->getPosition(position);

           ApplyForce(deltaTime);
           ApplyTorque(deltaTime);

           excelFile << currentTicks << "," << Bodyref->GetTorque() << "," << Bodyref->GetAngularAcceleration() << "," << Bodyref->GetAngularVelocity() << "," <<

               Bodyref->GetAngularPosition() << "," << Bodyref->GetForce().x << "," << Bodyref->GetForce().y << "," << Bodyref->GetAcceleration().x << "," <<

               Bodyref->GetAcceleration().y << "," << Bodyref->GetVelocity().x << "," << Bodyref->GetVelocity().y << "," <<

               converted.x << "," << converted.y << "," << std::endl;

           //DEBUG

          std::cout << "Time:" << currentTicks << "\n" << "Torque:" << Bodyref->GetTorque() << "\n" << "AngAccel:" << Bodyref->GetAngularAcceleration() << "\n" << "AngVelo:" << Bodyref->GetAngularVelocity()

               << "\n" << "angle:" << Bodyref->GetAngularPosition() << "\n" << "forcex:" << Bodyref->GetForce().x << "\n" << "forcey:" << Bodyref->GetForce().y << "\n" << "accel.x" << Bodyref->GetAcceleration().x <<

               "\n" << "accel.y:" << Bodyref->GetAcceleration().y << "\n" << "velocityx:" << Bodyref->GetVelocity().x << "\n" << "velocityy:" << Bodyref->GetVelocity().y << "\n"

               << "Posx:" << converted.x << "\n" << "Posy:" << converted.y << std::endl;
           //DEBUG
           prevTicks = currentTicks;
       }
       SimulationEventUpdate(deltaTime);
	   world->UpdateWorld(camera);
	   world->Update(deltaTime);
}

void Scene2::ApplyTorque(float deltatime_)
{
    spaceShip->GetComponent<Physics>()->ApplyTorque(spaceShip->GetComponent<Body>()->GetTorque(),deltatime_, spaceShip->GetComponent<Body>());
}

void Scene2::ApplyForce(float deltatime_)
{
    spaceShip->GetComponent<Physics>()->ApplyForce(spaceShip->GetComponent<Body>()->GetForce(),deltatime_, spaceShip->GetComponent<Body>());
}

void Scene2::SimulationEventUpdate(float deltaTime_)
{
    if (prevTicks >0.0f)
    {
        prevTicks = prevTicks / 1.0f;
        prevTicks = floor(prevTicks);
    }
    if (currentTicks == 5.0f)
    {
        float torque = 6.291 * powf(10, 8);
        MATH::Vec3 force =spaceShip->GetComponent<Body>()->GetForce();
        force /= 2;
        spaceShip->GetComponent<Body>()->SetForce(force);
        spaceShip->GetComponent<Body>()->SetTorque(torque);
    }
    else if (totalTime == 30.0f)
    {
        spaceShip->GetComponent<Body>()->SetForce(MATH::Vec3());
        spaceShip->GetComponent<Body>()->SetTorque(0.0f); 
    }
    else if (totalTime == 60.0f)
    {
        excelFile.close();
        std::cout << "Simulation ended" << std::endl;
    }
    //TotalTime is the amount of "real" time that has passed on this machine
    currentTicks = totalTime;
    if (currentTicks > 0.0f)
    {
        currentTicks = currentTicks / 1.0f;
        currentTicks = floor(currentTicks); //round it to a whole number
    }
    totalTime += deltaTime_;
}

void Scene2::Render()
{
    world->Render();
}

void Scene2::HandleEvents(const SDL_Event& sdlEvent)
{
    
    if (sdlEvent.type==SDL_QUIT)
    {
        excelFile.close();
    }
    
}

