/*
 * ManualMesh.h
 *
 *  Created on: Jan 4, 2013
 *      Author: rulk
 */

#ifndef MANUALMESH_H_
#define MANUALMESH_H_
#include <list>
#include "TriangelMesh.h"
namespace StingRay
{

class ManualMesh
{
	std::list<Vector4Impl> vertex;
	std::list<Vector4Impl> colors;
	std::list<Vector4Impl> normals;
	std::list<Vector2Impl> uvs;
	std::list<uInt> strip;

	bool begun;
	Material * material;
	void clear();
public:
	ManualMesh();

	void begin(Material * mat);
	void beginStrip();

	/**
	 * add a new vertex and start editing it
	 */
	void position(const Fvec4 & position);
	void position(float x,float y,float z,float w =1.0);

	void duplicateLast();

	/**
	 * set current vertexes color;
	 */
	void color(const Fvec4 & color);

	/**
	 * set current vertex normal
	 */
	void normal(const Fvec4 & normal);

	/**
	 * set current vertex uv
	 */
	void textureCoord(const Fvec2 & uv);

	/**
	 * Can be called multiple times, it just produces new TriangelMesh from current data
	 */
	TriangelMesh * getTriangelMesh();

	/**
	 * clears current data
	 */
	TriangelMesh * end();
	virtual ~ManualMesh();
};

} /* namespace StingRay */
#endif /* MANUALMESH_H_ */
