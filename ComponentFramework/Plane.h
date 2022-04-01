#ifndef PLANE_H
#define PLANE_H
#include "VMath.h"
#include "Vector.h"
#include "Matrix.h"
#include "MMath.h"
using namespace MATH;
class Body;
/*
* There is only one problem for the plane class and I can see it now. 
* Basically the Plane Object, has to be static and can't really move because we are using its normal to caculate the collison response.
* This also means that we need to correctly setup the normal in order for the collision detection to work properly unless it won't. 
*/
class Plane
{
public:
	/* Represent plane using x,y,z and d as the 4th component 
	* where x,y,z are the components of the normal vector 
	* d is the distance to a parallel plane going through the origin 
	* d = -N dot (point on plane) 
	*/
	Plane(float x_, float y_, float z_, float d_);
	Plane();
	~Plane();
	float Distance(const Body& PhysicsObject);
	///Set the Height and Width of the Plane
	void SetSize(int width_ , int height_);
	///Set the angle that the plane is at
	float GetWidth();
	float GetHeight();
	float GetTheta();
	/// Set Position of the plane
	void SetPosition(Vec3 position_);
	Vec3 GetPosition();
	/// Vec3 the normal point that is perpendicular to the plane
	Vec3 GetNormal();
 private:
	Vec4 plane;
	Matrix4 transform;
	float angle;
	
};
#endif //!Plane
