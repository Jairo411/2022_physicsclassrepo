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
	cameraPositionM[14] = 0.0f;
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

void Camera::Translate(MATH::Vec3 translate_)
{
	cameraPositionM[12] += translate_.x;
	cameraPositionM[13] += translate_.y;
}

MATH::Vec3 Camera::GetPosition()
{
	MATH::Vec3 converted = MATH::Vec3();
	converted.x = cameraPositionM[12] - cameraOrigin.x;
	converted.y = cameraOrigin.y - cameraPositionM[13];
	return converted;
}

MATH::Vec2 Camera::GetCameraDraw()
{
	MATH::Vec2 draw = MATH::Vec2();
	draw.x = drawWidth;
	draw.y = drawHeight;
	return draw;
}

MATH::Vec3 Camera::GetOrigin()
{
	return cameraOrigin;
}
