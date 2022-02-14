#ifndef CAMERA_H
#define CAMERA_H
#include "Matrix.h"
#include "Vector.h"
class Camera
{
public:
	Camera();
	~Camera();
	bool OnCreate();
	void OnDestroy();
	void SetOrigin(int width_, int height_);
	/// Set a Position to follow
	void SetFollowPosition(MATH::Vec3 FollowPosition_);
	void Update(float deltaTime_);
	/// Using the worldPosition Matrix which is the center of the screen
	/// I create the "Actual" world coordinates in realtion to where the matrix is compared to the origin
	void UpdateScreenPosition();

	static MATH::Vec2 getWorldPosition(MATH::Vec2 position);
	static MATH::Vec2 porigin;
	static MATH::Matrix3 worldPosition;
private:
	MATH::Vec3 origin;
	MATH::Vec3 followPosition; 
	MATH::Vec2 ConvertedScreenCoords;
	
};
#endif // !CAMERA_H


