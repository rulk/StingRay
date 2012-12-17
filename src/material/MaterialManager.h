/*
 * MaterialManager.h
 *
 *  Created on: Dec 17, 2012
 *      Author: rulk
 */

#ifndef MATERIALMANAGER_H_
#define MATERIALMANAGER_H_

#include "ConfigLoader.h"
#include "Material.h"
namespace StingRay {

class MaterialManager: protected StingRay::ConfigLoader
{
	std::string materialFolder;
	MaterialProgramManager * programManager;
	VoidStream * stream;

	std::map<std::string,Material*> materials;

public:
	MaterialManager(const std::string & materialFolder, const std::string & programFolder);
	void loadFile(const std::string & fileName);
	void compile();
	Material * getMaterial(const std::string & name);
	VoidStream * getCompiledStream();
	virtual ~MaterialManager();
};

} /* namespace StingRay */
#endif /* MATERIALMANAGER_H_ */
