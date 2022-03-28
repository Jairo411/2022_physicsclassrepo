#include "Physics.h"
#include "Body.h"
#include "Plane.h"
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

void Physics::ApplyTorque(const float deltaTime_, Body* object_)
{
}

void Physics::ApplyForce(const float deltaTime_, Body* object_)
{
}

bool Physics::SphereToSphereCollisionDetected(const Body& sphere0_, const Body& sphere1_)
{
    float distanceM = 0.0f;
    float radiusSum = 0.0f;
    Body s0 = sphere0_;
    Body s1 = sphere1_ ;
    //Get the vector pointing from the first sphere to the second sphere
    MATH::Vec3 distance = s0.GetPosition() - s1.GetPosition();
    //Add the spheres radiis.
    radiusSum = s0.GetRadius() + s1.GetRadius();
    //Get the magnitude of the distance vector, to use in comparsion with the radiusSum variable
    distanceM = MATH::VMath::mag(distance);
    if (distanceM<=radiusSum)
    {
        std::cout << "Collision Detected with sphere" << std::endl;
        return true;
    }
    return false;
}

bool Physics::SphereToPlaneCollisionDetected(const Body sphere_, const Plane plane_)
{
   /* How this collision works is, get two edges of a square/rectangle/plane 
   *  Then check the closest two edges of the square to the circle.
   *  Then after the collision dectection has picked two sides, start testing if a collision has happened
   */
    Body s = sphere_;
    Plane p = plane_;

    Vec3 pS = s.GetPosition();
    Vec3 pP = p.GetPosition();
    Vec3 distance = Vec3();
    
    Vec3 edge = Vec3();
    if (pS.x <= pP.x)
    {
        edge.x = pP.x; //left edge
    }
    else if (pS.x > pP.x+p.GetWidth())
    {
        edge.x = pP.x + p.GetWidth(); //right edge
    }
    if (pS.y<=pP.y)
    {
        edge.y = pP.y; //top edge/left edge if the object you're working with is a square
    }
    else if (pS.y>pP.y + p.GetHeight())
    {
        edge.y =  pP.y + p.GetHeight(); //bottom edge
    }
    ///get the distance between the circle and the closest edge
    distance = pS - edge;
    ///get the length of the vector
    float distanceM = MATH::VMath::mag(distance);
    if (distanceM <= s.GetRadius())
    {
        std::cout << "Collision Detected with Static Wall" << std::endl;
        return true;
    }
    return false;
}

void Physics::SphereToSphereCollisionResponse(Body& sphere0_, Body& sphere1_)
{
}

void Physics::SphereToStaticSphereCollisionResponse(Body& sphere0_, const Body& staticSphere_)
{
}

void Physics::SpherePlaneCollisionResponse(Body& sphere0_, const Plane& plane_)
{
    /// There are two types of wall collisions 
   /// 1.Simple Collisions 
   /// angle of incidence = angle of reflection 
   /// 2. Collision with Non-Axis Aligned Planes 
   /// 
     
    Plane plane = plane_;
    //Simple Collision
    if (plane.GetTheta() == 0.0f || plane.GetTheta() == 90.0f || plane.GetTheta() == 180.0f || plane.GetTheta() == 360.0f)
    {
        
    }
    else //Collision with Non-Axis Aligned Planes
    {

    }

}

void Physics::ApplyForce(MATH::Vec3 force_, const float deltaTime_, Body* object_)
{
    MATH::Vec3 force = MATH::Vec3();
    force = force_;
    force.z = 0;
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



    MATH::Vec3 position = MATH::Vec3();

    position = MATH::Vec3(object_->GetPosition().x + object_->GetVelocity().x + halfaccel.x*deltaTime_,
    object_->GetPosition().y + object_->GetVelocity().y +halfaccel.y*deltaTime_,
    0.0f);

    object_->SetVelocity(velocity);
    object_->SetPosition(position);
}

