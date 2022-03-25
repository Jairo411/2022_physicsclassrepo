#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include "Actor.h"
#include "VMath.h"
#include "Matrix.h"
#include <SDL_events.h>
class Body : public Component
{
public:
	Body(Component* parent_);
	virtual ~Body();
	virtual void Update(const float deltaTime_) override;

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;

	virtual void Render()override;

	void SetMass(float mass_);
	void SetRotationalInertia(float rotationalInertia_);
	void SetRadius(float radius_);

	void SetPosition(MATH::Vec3 position_);
	void SetVelocity(MATH::Vec3 velocity_);
	void SetAcceleration(MATH::Vec3 acceleration_);
	void SetForce(MATH::Vec3 force_);
	

	void SetAngle(float angularPosition_);
	void SetAngularVelocity(float angularVelocity_);
	void SetAngularAcceleration(float angularAcceleration_);
	void SetTorque(float torque_);
	void SetRotationMatrix(MATH::Matrix3 rotation_); // remove this, like now

	float GetTorque();
	float GetMass();
	float GetRotationalInertia();
	float GetRadius();

	MATH::Vec3 GetPosition();
	MATH::Vec3 GetVelocity();
	MATH::Vec3 GetAcceleration();
	MATH::Vec3 GetForce();
	MATH::Matrix3 GetRotationMatrix();

	float GetAngularPosition();
	float GetAngularVelocity();
	float GetAngularAcceleration();

private:
	float mass,rotationalInertia,torque;
	float angle,angularVel,angularAcc;
	float radius;
	MATH::Vec3 position, velocity, acceleration;
	MATH::Vec3 force;
	MATH::Matrix3 rotationMatrix;
};
#endif // !BODY_H

