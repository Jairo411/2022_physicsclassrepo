#include "Physics.h"
#include "Body.h"
Physics::Physics(Component* parent_): Component(parent_)
{
}

Physics::~Physics()
{
}

bool Physics::OnCreate()
{
    return false;
}

void Physics::OnDestroy()
{
}

void Physics::Update(const float deltaTime_)
{
}

void Physics::Render() 
{
}


void Physics::ApplyTorque(float torque_,const float deltaTime_, Body* object_)
{
    float acceleration = torque_ / object_->GetRotationalInertia();
    object_->SetAngularAcceleration(acceleration);
    float velocity = object_->GetAngularVelocity() + acceleration * deltaTime_;

 
    float halfaccel = acceleration / 2;
    float angle =  object_->GetAngularPosition()+object_->GetAngularVelocity() +halfaccel;

    object_->SetAngularVelocity(velocity);
    object_->SetAngle(angle);

    


}

void Physics::ApplyForce(MATH::Vec3 force_, const float deltaTime_, Body* object_)
{
    MATH::Vec3 force;
    force = force_;
    force.z = 1;
    MATH::Matrix3 rotation = object_->GetRotationMatrix();

    float mass = object_->GetMass();

   //First row
   rotation[0] = cosf(object_->GetAngularPosition());
   rotation[3] = sinf(object_->GetAngularPosition()) * -1.0f;
   //Second Row
   rotation[1] = sinf(object_->GetAngularPosition());
   rotation[4] = cosf(object_->GetAngularPosition());

   force = rotation * force;
   object_->SetForce(force);

    MATH::Vec3 acceleration = force / mass;
    object_->SetAcceleration(acceleration);

    MATH::Vec3 halfaccel = MATH::Vec3();

    halfaccel.x = acceleration.x / 2;
    halfaccel.y = acceleration.y / 2;

    MATH::Vec3 velocity = MATH::Vec3();

    velocity.x = object_->GetVelocity().x + acceleration.x * deltaTime_;
    velocity.y = object_->GetVelocity().y + acceleration.y * deltaTime_;

  //  MATH::Vec3 acceleration = force / mass;

  //  MATH::Vec3 halfaccel = acceleration / 2;

  //  MATH::Vec3 velocity = object_->GetVelocity() + acceleration * deltaTime_;

    MATH::Vec3 position = MATH::Vec3();

    position = MATH::Vec3(object_->GetPosition().x + object_->GetVelocity().x + halfaccel.x*deltaTime_,
    object_->GetPosition().y + object_->GetVelocity().y +halfaccel.y*deltaTime_,
    0.0f);

    object_->SetVelocity(velocity);
    object_->SetPosition(position);
}

