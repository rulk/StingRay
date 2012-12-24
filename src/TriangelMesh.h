/*
 * TriangelMesh.h
 *
 *  Created on: Dec 23, 2012
 *      Author: rulk
 */

#ifndef TRIANGELMESH_H_
#define TRIANGELMESH_H_

#include "Randerable.h"

namespace StingRay
{

class TriangelMesh: public Renderable
{
	std::vector<Vector4Impl> faces;
	std::vector<Vector4Impl> vertexes;
	std::vector<Vector4Impl> normals;


public:
	TriangelMesh(size_t vertexes,size_t faces);

	void setVertex(const Fvec4 & vertex,size_t i);
	void setFace(const Fvec4 & normal,size_t i);
	void setNormal(const Fvec4 & normal,size_t i);

	virtual ~TriangelMesh();
};

} /* namespace StingRay */
#endif /* TRIANGELMESH_H_ */
