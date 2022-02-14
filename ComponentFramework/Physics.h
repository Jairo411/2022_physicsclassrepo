#ifndef PHYSICS_H
#define PHYSICS_H
#include "Component.h"
#include "Vector.h"
class Body;
class Physics : public Component
{
public:
	Physics(Component* parent_);
	virtual ~Physics();
	virtual bool OnCreate()override;
	virtual void OnDestroy()override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render();
	//Updates angular acceleration	using a= τ/I
	// and angular velocity/accelerate and angle 
	void ApplyTorque(float torque_,const float deltaTime_, Body* object_);
	//Updates acceleration using F/m 
	// and linear positions, velocity, and acceleration
	void ApplyForce(MATH::Vec3 force_, const float deltaTime_, Body* object_);
};
#endif 
