/*
 * Material.h
 *
 *  Created on: Dec 17, 2012
 *      Author: rulk
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "ConfigLoader.h"

namespace StingRay
{

class Material
{
	ConfigNode * root;
	const size_t offset;
	const MaterialManager * parentManager;
	const MaterialProgramParam * program;
	friend class MaterialManager;
	Material(ConfigNode * root,size_t offset,MaterialManager * parent,MaterialProgramParam * program);
	virtual ~Material();
public:

	std::string getName();
	void setParameter(const std::string & name,const std::vector<std::string> & value);
	void setParameter(ConfigNode * node);
	Real getParameterReal(const std::string & name);
	StreamData getParameter(const std::string & name);


};

} /* namespace StingRay */
#endif /* MATERIAL_H_ */
