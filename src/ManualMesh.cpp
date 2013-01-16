/*
 * ManualMesh.cpp
 *
 *  Created on: Jan 4, 2013
 *      Author: rulk
 */

#include "ManualMesh.h"

namespace StingRay
{

ManualMesh::ManualMesh()
{
	clear();
}
void ManualMesh::clear()
{
	material = NULL;
	begun = false;
	strip.clear();
	vertex.clear();
	colors.clear();
	normals.clear();
	uvs.clear();

}
void ManualMesh::begin(Material * mat)
{

	if(mat == NULL)
		THROW(0,"Can't create ManualMesh with NULL pointer to material");
	clear();
	material = mat;
	begun = true;
}
void ManualMesh::beginStrip()
{
	if(!begun)return;
	strip.push_back(vertex.size());
}
void ManualMesh::position(const Fvec4 & position)
{
	if(!begun)return;
	if(vertex.size() ==0 && strip.size() == 0)beginStrip();
	vertex.push_back(position);
}
void ManualMesh::position(float x,float y,float z,float w)
{
	if(!begun)return;
	if(vertex.size() ==0 && strip.size() == 0)beginStrip();
	vertex.push_back(Vector4I(x,y,z,w));
}
void ManualMesh::duplicateLast()
{
	if(!begun || vertex.size() == 0)return;
	vertex.push_back(*(vertex.end()--));
}
void ManualMesh::color(const Fvec4 & color)
{
	if(!begun|| vertex.size() == 0)return;
	for(;colors.size() != vertex.size();)
		colors.push_back(color);
	//overriding if existing
	colors.pop_back();
	colors.push_back(color);
}
void ManualMesh::normal(const Fvec4 & normal)
{
	if(!begun || vertex.size() == 0)return;
	while(normals.size() != vertex.size())
		normals.push_back(normal);
	//overriding if existing
	normals.pop_back();
	normals.push_back(normal);

}
void ManualMesh::textureCoord(const Fvec2 & uv)
{
	if(!begun|| vertex.size() == 0)return;
	while(uvs.size() != vertex.size())
		uvs.push_back(uv);
	//overriding if existing
	uvs.pop_back();
	uvs.push_back(uv);
}
TriangelMesh * ManualMesh::end()
{
	TriangelMesh * mesh = getTriangelMesh();
	clear();
	return mesh;

}
TriangelMesh * ManualMesh::getTriangelMesh()
{
	TriangelMesh * mesh = new TriangelMesh(material);
	mesh->setVertexData(vertex.begin(),vertex.end(),vertex.size());
	mesh->setStripsData(strip.begin(),strip.end(),strip.size());

	if(uvs.size() != 0 && uvs.size() != vertex.size())
		textureCoord(Fvec2(0,0));
	if(uvs.size( ) != 0)
		mesh->setUvData(uvs.begin(),uvs.end(),uvs.size());

	if(colors.size() != 0 && colors.size() != vertex.size())
		color(Fvec4(0,0,0,0));
	if(colors.size() != 0)
		mesh->setColorData(colors.begin(),colors.end(),colors.size());

	if(normals.size() == 0 && normals.size() != vertex.size())
		normal(Fvec4(0,1,0,0));
	if(normals.size() != 0)
		mesh->setNormalData(normals.begin(),normals.end(),normals.size());
	return mesh;
}
ManualMesh::~ManualMesh()
{
	// TODO Auto-generated destructor stub
}

} /* namespace StingRay */
