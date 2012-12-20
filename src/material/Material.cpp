/*
 * Material.cpp
 *
 *  Created on: Dec 17, 2012
 *      Author: rulk
 */

#include "Material.h"
#include "Exception.h"
namespace StingRay
{

Material::Material(ConfigNode * root,size_t offset,MaterialManager * parent,MaterialProgramParam * program):
		root(root),offset(offset),parentManager(parent),program(program)
{

	if(root == NULL || parent == NULL || program == NULL )
		THROW(0,"Can't create un-initialized material!");
}
std::string Material::getName()
{
	return root->getName();
}
void Material::setParameter(const std::string & name,const std::vector<std::string> & value)
{
	ConfigNode * child = root->findChild(name,false);
	if(child ==  NULL)
	{
		ConfigNode * child = new ConfigNode(root,name);
	}
	child->clearValues();
	std::vector<std::string>::iterator it = value.begin();
	while(it != value.end())
	{
		child->addValue(*it);
		it++;
	}

}
void Material::setParameter( ConfigNode * node)
{
	root->addChild(node,true);
}
Real Material::getParameterReal(const std::string & name)
{
	ConfigNode * node = root->findChild(name);
	if (node == NULL || node->getValues().size() < 1)
		return RealI(0);
	return RealI(node->getValue(0));
}
Vector2Impl Material::getParameterVector2(const std::string & name)
{
	ConfigNode * node = root->findChild(name);
	if (node == NULL || node->getValues().size() < 2)
		return Vector2I(0, 0);
	return Vector2I(node->getValue(0), node->getValue(1));
}
Vector3Impl Material::getParameterVector3(const std::string & name)
{
	ConfigNode * node = root->findChild(name);
	if (node == NULL || node->getValues().size() < 3)
		return Vector3I(0, 0, 0);
	return Vector3I(node->getValue(0), node->getValue(2), node->getValue(3));
}
Vector4Impl Material::getParameterVector4(const std::string & name)
{
	ConfigNode * node = root->findChild(name);
	if (node == NULL || node->getValues().size() < 4)
		return Vector4I(0, 0, 0, 0);
	return Vector4I(node->getValue(0), node->getValue(2), node->getValue(3),
			node->getValue(4));
}
StreamData Material::getParameter(const std::string & name)
{
	ConfigNode * node = root->findChild(name);
}
Material::~Material()
{
	// material is just a helper class it does not manage any data
}

} /* namespace StingRay */
