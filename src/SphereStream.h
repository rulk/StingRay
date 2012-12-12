/*
 * SphereStream.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef SPHERESTREAM_H_
#define SPHERESTREAM_H_
//Basic stream to sphere buffer
#include "implementation.h"
namespace StingRay
{
class SphereStream
{
	Vector4ImplStream *position;
	Vector4ImplStream *radiusColor;
public:

	SphereStream(size_t size,SteramType type = STREAM_WRITE);
	void put(Vector4Impl position,Real r,Vector3Impl color);
	void flush();
	const Vector4ImplStream * getPositionStream()const
	{
		return position;
	}
	const Vector4ImplStream * getRadiusColorStream() const
	{
		return radiusColor;
	}
	virtual ~SphereStream();
};
}
#endif /* SPHERESTREAM_H_ */
