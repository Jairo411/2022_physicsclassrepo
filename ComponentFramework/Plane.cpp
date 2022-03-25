#include "Plane.h"
#include "Body.h"

Plane::Plane(float x_, float y_, float z_, float d_)
{
    plane.x = x_;
    plane.y = y_;
    plane.z = z_;
    plane.w = d_; // The math here is -N dot (point on plane) 
    // The normal of a 2D plane (changeInTheY , -changeintheX)
}

Plane::Plane()
{
}

Plane::~Plane()
{
}

void Plane::SetSize(int width_, int height_)
{
    transform[0] = width_;
    transform[1] = height_;
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

void Plane::SetTheta(float theta_)
{
    transform[0] = theta_;
    transform[4] = theta_;
    transform[1] = theta_;
    transform[5] = theta_;   
}

float Plane::GetTheta()
{
    //Only need to retrieve theta in one of the matrix columns because theta is the same in all four.
    return transform[0];
}

float Plane::GetWidth()
{
    return transform[0];
}

float Plane::GetHeight()
{
    return transform[5];
}

Vec3 Plane::GetPosition()
{
    Vec3 position = Vec3();
    position.x = plane.x;
    position.y = plane.y;
    position.z = plane.z;
    return position;
}
