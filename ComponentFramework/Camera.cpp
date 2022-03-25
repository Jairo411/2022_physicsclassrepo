#include "Camera.h"

Camera::Camera()
{
	cameraOrigin = MATH::Vec3();
	ViewM = MATH::Matrix4();
}

Camera::~Camera()
{
}

bool Camera::OnCreate()
{
	ViewM[12] = cameraOrigin.x;
	ViewM[13] = cameraOrigin.y;
	ViewM[14] = 0.0f;
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
	ViewM[12] += translate_.x;
	ViewM[13] += translate_.y;
}

MATH::Vec3 Camera::GetPosition()
{
	MATH::Vec3 converted = MATH::Vec3();
	converted.x = ViewM[12] - cameraOrigin.x;
	converted.y = cameraOrigin.y - ViewM[13];
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
