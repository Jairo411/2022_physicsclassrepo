#include "Body.h"

Body::Body(Component* parent_) : Component(parent_)  // This is called a default constructor or default intialization
{
	position = MATH::Vec3();
	velocity = MATH::Vec3();
	acceleration = MATH::Vec3();
	rotationMatrix = MATH::Matrix3();
	rotationMatrix[8] = 0.0f;
	mass = 0.0f;
	rotationalInertia = 0.0f;
	angle = 0.0f;
	angularVel = 0.0f;
	angularAcc = 0.0f;
}
Body::~Body()
{
}

void Body::Update(const float deltaTime_)
{

}

bool Body::OnCreate()
{
	
	return true;
}

void Body::OnDestroy()
{
}

void Body::Render() 
{
}

void Body::SetMass(float mass_)
{
	mass = mass_;
}

void Body::SetRotationalInertia(float rotationalInertia_)
{
	rotationalInertia = rotationalInertia_;
}

void Body::SetRadius(float radius_)
{
	radius = radius_;
}

void Body::SetPosition(MATH::Vec3 position_)
{
	position = position_;
}

void Body::SetVelocity(MATH::Vec3 velocity_)
{
	velocity = velocity_;
}

void Body::SetAcceleration(MATH::Vec3 acceleration_)
{
	acceleration = acceleration_;
}

void Body::SetForce(MATH::Vec3 force_)
{
	force = force_;
}

void Body::SetAngle(float angularPosition_)
{
	angle = angularPosition_;
}

void Body::SetAngularVelocity(float angularVelocity_)
{
	angularVel = angularVelocity_;
}

void Body::SetAngularAcceleration(float angularAcceleration_)
{
	angularAcc = angularAcceleration_;
}

void Body::SetTorque(float torque_)
{
	torque = torque_;
}

void Body::SetRotationMatrix(MATH::Matrix3 rotation_)
{
	rotationMatrix = rotation_;
}

float Body::GetTorque()
{
	return torque;
}

float Body::GetMass()
{
	return mass;	
}

float Body::GetRotationalInertia()
{
	return rotationalInertia;
}

float Body::GetRadius()
{
	return radius;
}

MATH::Vec3 Body::GetPosition()
{
	return position;
}

MATH::Vec3 Body::GetVelocity()
{
	return velocity;
}

MATH::Vec3 Body::GetAcceleration()
{
	return acceleration;
}

MATH::Vec3 Body::GetForce()
{
	return force;	
}

MATH::Matrix3 Body::GetRotationMatrix()
{
	return rotationMatrix;
}

float Body::GetAngularPosition()
{
	return angle;
}

float Body::GetAngularVelocity()
{
	return angularVel;
}

float Body::GetAngularAcceleration()
{
	return angularAcc;
}
