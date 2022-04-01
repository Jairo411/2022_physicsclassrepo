#include "Plane.h"
#include "Body.h"

Plane::Plane(float x_, float y_, float z_, float d_)
{
    plane.x = x_;
    plane.y = y_;
    plane.z = z_;
    plane.w = d_; 

    // The math here is -N dot (point on plane) 
    // The normal of a 2D plane (changeInTheY , -changeintheX)
}

Plane::Plane()
{
    angle = 0.0f;
}

Plane::~Plane()
{
}


float Plane::Distance(const Body& PhysicsObject)
{
    float distanceFromPlane = 0.0f;
    Body physicsObject = physicsObject;
    Vec3 planePos = Vec3();
    Vec3 distance = Vec3();
    planePos.x = plane.x;
    planePos.y = plane.y;
    planePos.z = plane.z;
    distanceFromPlane = MATH::VMath::dot(distance,physicsObject.GetPosition()) - physicsObject.GetRadius();
    return distanceFromPlane;
}

void Plane::SetSize(int width_, int height_)
{
    transform[0] = width_;
    transform[5] = height_;
}

float Plane::GetWidth()
{
    return transform[0];
}

float Plane::GetHeight()
{
    return transform[5];
}

float Plane::GetTheta()
{
    return angle;
}

void Plane::SetPosition(Vec3 position_)
{
    transform[12] = position_.x;
    transform[13] = position_.y;
    transform[14] = position_.z;
}

Vec3 Plane::GetPosition()
{
    Vec3 position;
    position.x = transform[12];
    position.y = transform[13];
    position.z = transform[14];
    return position;
}

Vec3 Plane::GetNormal()
{
    Vec3 normal = Vec3();
    normal.x = plane.x;
    normal.y = plane.y;
    normal.z = plane.z;
    return normal;
}

