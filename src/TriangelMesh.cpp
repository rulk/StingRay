/*
 * TriangelMesh.cpp
 *
 *  Created on: Dec 23, 2012
 *      Author: rulk
 */

#include "TriangelMesh.h"

namespace StingRay
{

TriangelMesh::TriangelMesh(Material * mat):Renderable(mat)
{
	hasNormals = false;
	hasColors = false;
	hasStrips = false;
	hasUvs = false;
	hasVertex = false;

}

TriangelMesh::~TriangelMesh()
{
	// TODO Auto-generated destructor stub
}
size_t TriangelMesh::getNumDataChunks()
{
	size_t num = 2;
	if(hasNormals) num++;
	if(hasColors) num++;
	if(hasUvs) num++;
	return num;
}
const void* TriangelMesh::getData(size_t chunk)
{
	if(hasVertex == false || hasStrips == false)
		THROW(0,"TriangelMesh must contain vertex data to be rendered!");
	if(chunk == 0)
		return formatHeader();
	if(chunk == 1)
		return &strip.front();
	else if(chunk == 2)
	{

		return &vertex.front();
	}
	else if(chunk == 3)
	{
		if(hasNormals) return &normal.front();
		else if(hasColors) return &color.front();
		else if(hasUvs) return &uv.front();
	}
	else if(chunk == 4)
	{
		if(hasColors) return &color.front();
		else if(hasUvs) return &uv.front();

	}
	else if(chunk == 5 && hasUvs)
		return &uv.front();
	return 0;
}

size_t TriangelMesh::getDataChunkSize(size_t chunk)
{
	if(hasVertex == false || hasStrips == false)
			THROW(0,"TriangelMesh must contain vertex data to be rendered!");
	if (chunk == 0)
		return 5*sizeof(uInt);
	if (chunk == 1)
		return strip.size()*sizeof(uInt);
	else if (chunk == 2)
		return vertex.size()*sizeof(Vector4Impl);
	else if (chunk == 3)
	{
		if (hasNormals)
			return normal.size()*sizeof(Vector4Impl);
		else if (hasColors)
			return color.size()*sizeof(Vector4Impl);
		else if (hasUvs)
			return uv.size()*sizeof(Vector2Impl);
	}
	else if (chunk == 4)
	{
		if (hasColors)
			return color.size()*sizeof(Vector4Impl);
		else if (hasUvs)
			return uv.size()*sizeof(Vector2Impl);

	}
	else if (chunk == 5 && hasUvs)
		return uv.size()*sizeof(Vector2Impl);
	return 0;
}
void TriangelMesh::setVertex(const Fvec4 & vertex,size_t i)
{
	if(i < this->vertex.size())
		this->vertex[i] = vertex;
}
void TriangelMesh::setStripStart(uInt offset,size_t i)
{
	if(i < strip.size())
			strip[i] = offset;

}
void TriangelMesh::setNormal(const Fvec4 & normal,size_t i)
{
	if(i < this->normal.size())
		this->normal[i] = normal;
}
void TriangelMesh::setColor(const Fvec4 & color,size_t i)
{
	if(i < this->color.size())
		this->color[i] = color;
}
const uInt * TriangelMesh::formatHeader()
{
	header[HEADER_STRIPS_NUM] = strip.size();
	header[HEADER_VERTEX_NUM] = vertex.size();
	header[HEADER_UV_NUM] = uv.size();
	header[HEADER_COLOR_NUM] = color.size();
	header[HEADER_NORMAL_NUM] = color.size();
	return header;
}

} /* namespace StingRay */
