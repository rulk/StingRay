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
	bool hasNormals,hasColors,hasUvs,hasVertex,hasStrips;

	uInt header[5];

	std::vector<uInt> strip;
	std::vector<Vector4Impl> vertex;
	std::vector<Vector4Impl> color;
	std::vector<Vector4Impl> normal;
	std::vector<Vector2Impl> uv;


public:
	TriangelMesh(Material * mat);


	static const size_t HEADER_STRIPS_NUM = 0;
	static const size_t HEADER_VERTEX_NUM = 1;
	static const size_t HEADER_NORMAL_NUM = 2;
	static const size_t HEADER_COLOR_NUM  = 3;
	static const size_t HEADER_UV_NUM     = 4;

	bool getHasNormals(){return hasNormals;}
	bool getHasColors(){return hasColors;}
	bool getHasUvs(){return hasUvs;}

	const uInt * formatHeader();

	virtual Char getType(){return 1;}
	virtual size_t getNumDataChunks();
	virtual const void* getData(size_t chunk);
	virtual size_t getDataChunkSize(size_t chunk);


	void setVertex(const Fvec4 & vertex,size_t i);
	void setStripStart(uInt offset,size_t i);
	void setNormal(const Fvec4 & normal,size_t i);
	void setColor(const Fvec4 & color,size_t i);

	template<class InputIterator>
	void setVertexData(InputIterator vertexFirst,InputIterator vertexLast,size_t size)
	{
		vertex.resize(size);
		std::copy(vertexFirst,vertexLast,vertex.begin());
		hasVertex = true;
	}

	template<class InputIterator>
	void setColorData(InputIterator colorFirst,InputIterator colorLast,size_t size)
	{
		color.resize(size);
		std::copy(colorFirst,colorLast,color.begin());
		hasColors = true;
	}

	template<class InputIterator>
	void setNormalData(InputIterator normalFirst,InputIterator normalLast,size_t size)
	{
		normal.resize(size);
		std::copy(normalFirst,normalLast,normal.begin());
		hasNormals = true;
	}

	template<class InputIterator>
	void setStripsData(InputIterator stripFirst,InputIterator stripLast,size_t size)
	{
		strip.resize(size);
		std::copy(stripFirst,stripLast,strip.begin());
		hasStrips = true;
	}

	template<class InputIterator>
	void setUvData(InputIterator uvFirst,InputIterator uvLast,size_t size)
	{
		uv.resize(size);
		std::copy(uvFirst,uvLast,uv.begin());
		hasUvs = true;
	}

	virtual ~TriangelMesh();
};

} /* namespace StingRay */
#endif /* TRIANGELMESH_H_ */
