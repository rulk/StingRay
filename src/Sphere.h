/*
 * Sphere.h
 *
 *  Created on: Dec 22, 2012
 *      Author: rulk
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Randerable.h"

namespace StingRay
{

class Sphere: public Renderable
{
	Fvec4 position;
	Real radius;
public:
	Sphere(Material * mat,const Fvec4 & pos,Real radius);
	Fvec4 getPosition();
	Real getRadius();
	virtual Char getType();
	virtual size_t getDataSize();
	size_t getNumDataChunks();
	const void* getData(size_t chunk);
	size_t getDataChunkSize(size_t chunk);
	virtual ~Sphere();
};

} /* namespace StingRay */
#endif /* SPHERE_H_ */
