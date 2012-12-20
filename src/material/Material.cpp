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

Material::Material(ConfigNode * root,size_t offset,MaterialManager * parent,const MaterialProgram * program):
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
		child = new ConfigNode(root,name);
	}
	child->clearValues();
	std::vector<std::string>::const_iterator it = value.begin();
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
StreamData * Material::getParameter(const std::string & name,const std::string & type)
{
	ConfigNode * node = root->findChild(name);
	if (node != NULL )
		return constructTypeFromStrings(type,node->getValues());
	else
		THROW(0,"Parameter:"+name+" of type:"+type+"was requested in material:"+getName()+" but was not found!");

}
StreamData * Material::getParameter(unsigned int i)
{
	if(program->getParamCount() > i)
	{
		return getParameter(program->getParamName(i),program->getParamType(i));
	}
	return NULL;
}
bool Material::hasParameter(const std::string & name)
{
	ConfigNode * node = root->findChild(name);
		if (node != NULL )
			return true;
		return false;
}
Material::~Material()
{
	// material is just a helper class it does not manage any data
}

} /* namespace StingRay */
