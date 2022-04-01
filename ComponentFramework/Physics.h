#ifndef PHYSICS_H
#define PHYSICS_H
#include "Component.h"
#include "Vector.h"
#include "VMath.h"
class Body;
class Plane;
class Physics : public Component
{
public:
	Physics(Component* parent_);
	virtual ~Physics();
	virtual bool OnCreate()override;
	virtual void OnDestroy()override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render();
	///<summary>
	///Updates angular acceleration	using a= τ/I
	/// and angular velocity/accelerate and angle 
	///</summary>
	void ApplyTorque(float torque_,const float deltaTime_, Body* object_);
	/// Will apply torque that is saved in the Body object member variable. NOT IMPLEMENTED
	void ApplyTorque(const float deltaTime_, Body* object_);
	///<summary>
	/// Updates acceleration using F/m 
	/// and linear positions, velocity, and acceleration.
	/// Apply's a new force onto the body
	/// </summary> 
	void ApplyForce(MATH::Vec3 force_, const float deltaTime_, Body* object_);
	///Will apply force that is saved in the Body object member variable. NOT IMPLEMENTED
	void ApplyForce(const float deltaTime_, Body* object_);

	///Collision detection methods 
	static bool SphereToSphereCollisionDetection(const Body	&sphere0_, const Body& sphere1_);
	static bool SphereToPlaneCollisionDetection(const Body sphere_, const Plane plane_);
	///Collision response methods: 
	static void SphereToSphereCollisionResponse(Body& sphere0_, Body& sphere1_);
	static void SphereToStaticSphereCollisionResponse(Body& sphere0_, const Body& staticSphere_);
	static void SpherePlaneCollisionResponse(Body& sphere0_ ,const Plane& plane_);
};
#endif 
