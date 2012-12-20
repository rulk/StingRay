/*
 * MaterialManager.h
 *
 *  Created on: Dec 17, 2012
 *      Author: rulk
 */

#ifndef MATERIALMANAGER_H_
#define MATERIALMANAGER_H_
#include "implementation.h"
#include "ConfigLoader.h"
#include "MaterialProgramManager.h"

namespace StingRay {
class Material;
class MaterialManager: protected StingRay::ConfigLoader
{
	std::string materialFolder;
	MaterialProgramManager * programManager;
	VoidStream * stream;
	typedef std::map<std::string,Material*> MaterialMap;
	MaterialMap materials;

public:
	MaterialManager(const std::string & materialFolder, const std::string & programFolder);
	void loadFile(const std::string & fileName);
	void compile();
	const MaterialProgramManager * getProgramManager() const
	{
		return programManager;
	}
	std::string getCompiledSource()
	{
		return programManager->buildSource();
	}
	Material * getMaterial(const std::string & name);
	VoidStream * getCompiledStream();
	virtual ~MaterialManager();
};

} /* namespace StingRay */
#endif /* MATERIALMANAGER_H_ */
