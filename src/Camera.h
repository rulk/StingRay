/*
 * Camera.h
 *
 *  Created on: Dec 9, 2012
 *      Author: rulk
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include "implementation.h"
namespace SimpleRayTracer {

class Camera
{
	Vector4ImplStream * cameraStream;
public:
	Camera();
	Vector4Impl getPosition();
	void setPosition(Vector4Impl position);
	void setDirection(Vector4Impl direction,Vector4Impl up);
	void setFovRad(Real fovXRad,Real fovYRad);
	void setFovDeg(Real fovXDeg,Real fovYDeg);
	void flush();
	virtual ~Camera();

	const Vector4ImplStream * getCameraStream() const
	{
		return cameraStream;
	}


};

} /* namespace SimpleRayTracer */
#endif /* CAMERA_H_ */
