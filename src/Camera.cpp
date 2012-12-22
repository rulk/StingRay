/*
 * Camera.cpp
 *
 *  Created on: Dec 9, 2012
 *      Author: rulk
 */

#include "Camera.h"
#include "math.h"
namespace StingRay {
Vector4Impl norm(Vector4Impl vec)
{
	Real l = sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
	vec.x /=l;
	vec.y/=l;
	vec.z/=l;
	return vec;
}
Vector4Impl cross(Vector4Impl a,Vector4Impl b)
{
	Vector4Impl vec;
	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	return vec;
}
Camera::Camera() {

	cameraStream = new Vector4ImplStream(5,STREAM_READ);
	cameraStream->put(Vector4I(0,0,0,0));
	cameraStream->put(Vector4I(0,0,-1,0));
	cameraStream->put(Vector4I(120,120,3.14,3.14));
	cameraStream->put(Vector4I(1,0,0,0));
	cameraStream->put(Vector4I(0,1,0,0));

}

Camera::~Camera() {
	delete cameraStream;
}
Vector4Impl Camera::getPosition()
{
	Vector4Impl result;
	 cameraStream->get(0,result);
	 return result;
}
void Camera::setPosition(Vector4Impl position)
{
	cameraStream->replace(position,0);
}
void Camera::setDirection(Vector4Impl direction,Vector4Impl up)
{
	direction = norm(direction);
	cameraStream->replace(direction,1);
	Vector4Impl u = cross(direction,up);
	u = norm(u);
	up = cross(u,direction);
	cameraStream->replace(u,3);
	cameraStream->replace(up,4);

}
void Camera::setFovRad(Real fovXRad,Real fovYRad)
{
	Vector4Impl fov;
	fov.x = Core::getInstance()->width;
	fov.y = Core::getInstance()->height;
	fov.z = fovXRad;
	fov.w = fovYRad;
	cameraStream->replace(fov,2);
}
void Camera::setFovDeg(Real fovXDeg,Real fovYDeg)
{
	setFovRad(fovXDeg/180 * 3.14,fovYDeg/180 * 3.14);
}
void Camera::flush()
{
	cameraStream->flush();
}
} /* namespace SimpleRayTracer */
