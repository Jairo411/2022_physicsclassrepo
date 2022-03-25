#ifndef CAMERA_H
#define CAMERA_H
#include <vector>
#include "Matrix.h"
#include "Vector.h"
#include "Actor.h"
class Component;
/// <summary>
/// Camera origin, will always been in the middle of the screen 
/// The Camera should only have reference to the middle of the screen and nothing else 
/// </summary>
class Camera
{
public:
	Camera();
	Camera(float left, float right, float bottom, float top);
	~Camera();
	bool OnCreate();
	void OnDestroy();
	void SetOrigin(int width_, int height_);
	void Update(float deltaTime_);
	/// Move the origin of the camera, should only be set,
	/// if the screen changes sizes 
	void MoveOrigin(MATH::Vec3 origin_);
	void Translate(MATH::Vec3 translate_);
	MATH::Vec3 GetPosition();
	MATH::Vec2 GetCameraDraw();
	///Return the origin of the camera
	MATH::Vec3 GetOrigin();
private:
	int drawWidth;
	int drawHeight;
	///Camera Origin is the position in screen coordinates of where the centre of the centre is 
	MATH::Vec3 cameraOrigin;
	///Camera Position matrix is going to the virtual position of the camera
	MATH::Matrix4 ViewM;
	MATH::Matrix4 projection;
	MATH::Matrix4 view;
};
#endif // !CAMERA_H


