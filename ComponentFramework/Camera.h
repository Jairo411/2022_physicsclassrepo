#ifndef CAMERA_H
#define CAMERA_H
#include "Matrix.h"
#include "Vector.h"
class Component;
/// <summary>
/// Camera origin, will always been in the middle of the screen 
/// The Camera should only have reference to the middle of the screen and nothing else 
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();
	bool OnCreate();
	void OnDestroy();
	void SetOrigin(int width_, int height_);
	void Update(float deltaTime_);
	/// Move the origin of the camera, should only be set,
	/// if the screen changes sizes 
	void MoveOrigin(MATH::Vec3 origin_);
	MATH::Vec2 getPosition();
private:
	int drawWidth;
	int drawHeight;
	MATH::Vec3 cameraOrigin;
	///Camera Position matrix is going to the virtual position of the camera
	MATH::Matrix4 cameraPositionM;
};
#endif // !CAMERA_H


