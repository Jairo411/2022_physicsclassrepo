#include "Camera.h"
MATH::Matrix3 Camera::worldPosition = MATH::Matrix3();
MATH::Vec2 Camera::porigin = MATH::Vec2();

Camera::Camera()
{
	origin = MATH::Vec3();
	worldPosition = MATH::Matrix3();
	ConvertedScreenCoords = MATH::Vec2();
	followPosition = MATH::Vec3();
}

Camera::~Camera()
{
}

bool Camera::OnCreate()
{
	return true;
}

void Camera::OnDestroy()
{
}

void Camera::SetOrigin(int width_, int height_)
{
	origin.set(width_, height_, 1);
	worldPosition[6] = origin.x;
	worldPosition[7] = origin.y;	
}

void Camera::SetFollowPosition(MATH::Vec3 FollowPosition_)
{
	followPosition = FollowPosition_;
}

void Camera::Update(float deltaTime_)
{
	UpdateScreenPosition();
//	std::cout << "CSC X:" << ConvertedScreenCoords.x << std::endl;
//	std::cout << "CSC Y:" << ConvertedScreenCoords.y << std::endl;

}

void Camera::UpdateScreenPosition()
{
	worldPosition[6] = followPosition.x;
	worldPosition[7] = followPosition.y;
	if (worldPosition[6] >= origin.x || worldPosition[6] <= origin.x)
	{
		ConvertedScreenCoords.x = worldPosition[6] - origin.x;
	}
	if (worldPosition[7] >= origin.y || worldPosition[7] <= origin.y)
	{
		ConvertedScreenCoords.y = origin.y - worldPosition[7];
		
	}
}

MATH::Vec2 Camera::getWorldPosition(MATH::Vec2 position)
{
	MATH::Vec2 converted = MATH::Vec2();
	converted.x = position.x - porigin.x;
	converted.y = position.y - position.y;
	return converted;
}
