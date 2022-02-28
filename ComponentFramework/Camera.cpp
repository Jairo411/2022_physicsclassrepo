#include "Camera.h"

Camera::Camera()
{
	cameraOrigin = MATH::Vec3();
	cameraPositionM = MATH::Matrix4();
}

Camera::~Camera()
{
}

bool Camera::OnCreate()
{
	cameraPositionM[12] = cameraOrigin.x;
	cameraPositionM[13] = cameraOrigin.y;
	return true;
}

void Camera::OnDestroy()
{
}

void Camera::SetOrigin(int width_, int height_)
{
	drawWidth = width_;
	drawHeight = height_;
	int originx, originy;
	originx = drawWidth / 2;
	originy = drawHeight / 2;
	cameraOrigin.set(originx,originy, 1);
}

void Camera::Update(float deltaTime_)
{
}

void Camera::MoveOrigin(MATH::Vec3 origin_)
{
	cameraOrigin = origin_;
}

MATH::Vec2 Camera::getPosition()
{
	MATH::Vec2 converted = MATH::Vec2();
	converted.x = cameraPositionM[12] - cameraOrigin.x;
	converted.y = cameraOrigin.y - cameraPositionM[13];
	return converted;
}
