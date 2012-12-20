/*
 * Material.h
 *
 *  Created on: Dec 17, 2012
 *      Author: rulk
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "implementation.h"
#include "ConfigLoader.h"
#include "MaterialManager.h"
#include "MaterialProgramm.h"
namespace StingRay
{

class Material
{
	ConfigNode * root;
	const size_t offset;
	const MaterialManager * parentManager;
	const MaterialProgram * program;
	friend class MaterialManager;
	Material(ConfigNode * root,size_t offset,MaterialManager * parent,const MaterialProgram* program);
	virtual ~Material();
public:

	std::string getName();
	void setParameter(const std::string & name,const std::vector<std::string> & value);
	void setParameter(ConfigNode * node);
	StreamData * getParameter(const std::string & name,const std::string & type);
	StreamData * getParameter(unsigned int i);
	bool hasParameter(const std::string & name);


};

} /* namespace StingRay */
#endif /* MATERIAL_H_ */
