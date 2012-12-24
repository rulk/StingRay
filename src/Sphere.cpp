/*
 * Sphere.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: rulk
 */

#include "Sphere.h"

namespace StingRay
{
Sphere::Sphere(Material * mat,const Fvec4 & pos,Real radius):Renderable(mat)
{
	position = pos;
	this->radius = radius;
}
Fvec4 Sphere::getPosition()
{
	return position;
}
Real Sphere::getRadius()
{
	return radius;
}
Char Sphere::getType()
{
	return 3;
}
size_t Sphere::getDataSize()
{
	return sizeof(Real)+position.getISize();
}
size_t Sphere::getNumDataChunks()
{
	return 2;
}
void* Sphere::getData(size_t chunk)
{
	if(chunk == 0)return &radius;
	if(chunk == 1) return position.getIMemoryPtr();
	return NULL;
}
size_t Sphere::getDataChunkSize(size_t chunk)
{
	if(chunk == 0) return sizeof(Real);
	if(chunk == 1) return position.getISize();
	return 0;
}
Sphere::~Sphere()
{
	// TODO Auto-generated destructor stub
}

} /* namespace StingRay */
