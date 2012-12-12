/*
 * SphereStream.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#include "SphereStream.h"
namespace StingRay
{
SphereStream::SphereStream(size_t size,SteramType type) {
	// TODO Auto-generated constructor stub
	position  = new Vector4ImplStream(size,type);
	radiusColor = new Vector4ImplStream(size,type);
}

SphereStream::~SphereStream() {
	// TODO Auto-generated destructor stub
	delete position;
	delete radiusColor;
}
void SphereStream::put(Vector4Impl position,Real r,Vector3Impl color)
{
	this->position->put(position);
	Vector4Impl pc;
	pc.x = r;
	pc.y = color.x;pc.z = color.y;pc.w = color.z;
	radiusColor->put(pc);
}
void SphereStream::flush()
{
	position->flush();
	radiusColor->flush();
}
}
