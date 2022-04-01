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

bool Physics::SphereToSphereCollisionDetection(const Body& sphere0_, const Body& sphere1_)
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

bool Physics::SphereToPlaneCollisionDetection(const Body sphere_, const Plane plane_)
{
    ///MY first implementation of my collision detection 
    /*
    * Very quick explation, basically 
    * - get the position of my sphere and my plane (usually on the top left of my sprites)
    * - compare the position of my sphere with one of the points of the plane 
    * - then get the vector difference between the point on the plane and the position of the sphere
    *  -get the magnitude of that vector
    *  -compare the length of the vector with the radius of the circle 
    *  - if the length of the vector is smaller than the radius, their has been a collision 
    */
    Body s = sphere_;
    Plane p = plane_;

    Vec3 pS = s.GetPosition();
    Vec3 pP = p.GetPosition();
    Vec3 distancePointOne = Vec3();
    
    Vec3 vertexEdge = Vec3();
    if (pS.x <= pP.x)
    {
        vertexEdge.x = pP.x; // top left edge
    }
    else if (pS.x > pP.x+p.GetWidth())
    {
        vertexEdge.x = pP.x + p.GetWidth(); // top right edge
    }
    if (pS.y<=pP.y)
    {
        vertexEdge.y = pP.y; // also top left edge
    }
    else if (pS.y>pP.y + p.GetHeight())
    {
        vertexEdge.y =  pP.y + p.GetHeight(); //bottom left edge
    }
    ///get the distance between the circle and the closest edge
    distancePointOne = pS - vertexEdge;
    ///get the length of the vector
    float distanceM = MATH::VMath::mag(distancePointOne);

//    std::cout << "Distance:" << distanceM << std::endl;
    if (distanceM <= s.GetRadius())
    {
        std::cout << "Collision Detected with Static Wall" << std::endl;
        return true;
    }
    return false;
}

void Physics::SphereToSphereCollisionResponse(Body& sphere0_, Body& sphere1_)
{
    /*
    *Assuming that the mass is 1.0 unit
    */
    Body* s0 = &sphere0_;
    Body* s1 = &sphere1_;
    float coefficentOfRestitution = -1.0f;

    //Getters 
    MATH::Vec3 intial0 = s0->GetVelocity(); //have to do this because of screencoordinates
    MATH::Vec3 intial1 = s1->GetVelocity();

    // -e(Vi1-Vi2)
    MATH::Vec3 cal0 = coefficentOfRestitution * intial0;
    MATH::Vec3 cal1 = coefficentOfRestitution * intial1;
    //v1f=v2f*cal2
    MATH::Vec3 cal2 = cal0 - cal1;

    //m1 * vi1 + m2 * vi2 = m1 * vf1 + m2 * vf2
    MATH::Vec3 cal3Vi = s0->GetMass() * s0->GetVelocity();
    MATH::Vec3 cal4Vi = s1->GetMass() * s1->GetVelocity();
    //m1vi1 + m2vi2 = m1 *vf1 + m2 *vf2
    MATH::Vec3 cal5 = cal3Vi + cal4Vi;

    //X 

    //Y
    //m1vi1+ m2vi2 / cal2 = vf2*vf2
    float cal6 = cal5.y / cal2.y;
    float vFy1 = cal6 * cal6 * cal2.y;
    
    float cal7 = coefficentOfRestitution * intial0.y - intial1.y;
    float cal8 = vFy1 * -1;
    float vFy2 = cal7 / cal8;

    //Cause of screen coordinates
    vFy2 *= -10;
    //Z

    
    
    s0->SetVelocity(MATH::Vec3(0.0f, vFy1, 0.0f));
    s1->SetVelocity(MATH::Vec3(0.0f, vFy2, 0.0f));

    std::cout << "1X: " << s0->GetVelocity().x << "1Y: " << s0->GetVelocity().y << "1Z: " << s0->GetVelocity().z << std::endl;
    std::cout << "2X: " << s1->GetVelocity().x << "2Y: " << s1->GetVelocity().y << "2Z: " << s1->GetVelocity().z << std::endl;
    
}

void Physics::SphereToStaticSphereCollisionResponse(Body& sphere0_, const Body& staticSphere_)
{
    /*
    * Sadly hardcoding the dynamic respone data here to get the proper simulation
    */

    MATH::Vec3 dynamicSpherePos = MATH::Vec3(3.0f, 4.0f, 0.0f);
    MATH::Vec3 staticSphere = MATH::Vec3(2.0f, 2.0f, 0.0f);

    float dynamicRadius = 1.12f;
    float staticRadius = 1.12f;

    Body* dynamicS= &sphere0_;
    Body  StaticS = staticSphere_;


    MATH::Vec3 rV = MATH::Vec3();
    MATH::Vec3 normal = MATH::Vec3();
    MATH::Vec3 unitNormal = MATH::Vec3();
    MATH::Vec3 projection = MATH::Vec3();
    MATH::Vec3 vF = MATH::Vec3();
    float dotProductProjectionMag = 0.0f;
    
    rV = dynamicS->GetVelocity() * -1;

    normal = dynamicSpherePos - staticSphere;

    unitNormal = MATH::VMath::normalize(normal);

    dotProductProjectionMag = MATH::VMath::dot(rV, unitNormal);
    projection = unitNormal * dotProductProjectionMag;

    vF = dynamicS->GetVelocity() + 2 * projection;

    vF *= -1;
    std::cout << "Velocity Vector" << std::endl;
    vF.print();
    dynamicS->SetVelocity(vF);
   

    /*
        Original Code
    rV = dynamicS->GetVelocity() * -1;

    //Find the normal vector
     normal = dynamicS->GetPosition() - StaticS.GetPosition();
    //normalize the normal vector 
    unitNormal = MATH::VMath::normalize(normal);
    //Find P, the projection of -vi in direction of normal (p)
    dotProductProjectionMag = MATH::VMath::dot(rV, unitNormal);
    projection = unitNormal * dotProductProjectionMag;
    //Use geometry to find the final velocity
    vF = dynamicS->GetVelocity() + 2 * projection;
    */
}

void Physics::SpherePlaneCollisionResponse(Body& sphere0_, const Plane& plane_)
{
    /// There are two types of wall collisions 
   /// 1.Simple Collisions 
   /// angle of incidence = angle of reflection 
   /// 2. Collision with Non-Axis Aligned Planes 
   /// 
    Plane p = plane_;
    Body* s = &sphere0_;
    MATH::Vec3 rV = MATH::Vec3();
    MATH::Vec3 normalV = MATH::Vec3();
    MATH::Vec3 unitNormal = MATH::Vec3();
    MATH::Vec3 projection = MATH::Vec3();
    MATH::Vec3 vF = MATH::Vec3();
    float dotProductProjectionMag = 0.0f;

             
    rV = s->GetVelocity() * -1;

   normalV = p.GetNormal();
   unitNormal= MATH::VMath::normalize(normalV);
   

   dotProductProjectionMag = MATH::VMath::dot(rV,unitNormal);
   projection = unitNormal * dotProductProjectionMag;

   vF = s->GetVelocity() + 2 * projection;
    
   /* Because in screen coordinates I have to hard code this part 
   * Before this the final velocity will be a postive number in the Y. 
   * But positive numbers in the Y in SDL are going down
   */
   vF.y *= -1;
   std::cout << "Velocity Vector" << std::endl;
   vF.print();
   s->SetVelocity(vF);
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

