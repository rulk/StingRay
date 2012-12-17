/*
 * MaterialProgramManager.cpp
 *
 *  Created on: Dec 12, 2012
 *      Author: nrulk
 */
#include <sstream>
#include "MaterialProgramManager.h"
#include "Exception.h"
namespace StingRay
{
MaterialProgramManager::MaterialProgramManager(const std::string & programPath, const std::string & programExtension)
:programPath(programPath),progRamIdCounter(0),programExtension(programExtension)
{

}
const MaterialProgramm * MaterialProgramManager::getProgram(const std::string & name)
{
	std::map<std::string, unsigned int>::iterator it = programNameToId.find(name);
	if(it == programNameToId.end())
	{
		return loadProgram(name);
	}
	else return getProgramById(it->second);
}
const MaterialProgramm * MaterialProgramManager::getProgramById(unsigned int id)
{
	std::map<unsigned int,MaterialProgramm * >::iterator it = programs.find(id);
	if(it != programs.end())
		return *it->second;
	return NULL;
}
MaterialProgramm *  MaterialProgramManager::loadProgram(const std::string & name)
{

	std::string path;
	path = programPath + name+"."+programExtension;

	MaterialProgramm * program = new MaterialProgramm(name,path);
	programs[progRamIdCounter] = program;
	programNameToId[program->name] = progRamIdCounter;
	progRamIdCounter++;
	return program;
}
std::string MaterialProgramManager::buildSource()
{
	std::stringstream switchSource,functions;
	switchSource<<"float4 applyMaterial(int materialId, void * materialData)\n{\n";
	switchSource<<"\tswitch(materialId)\n\t{";
	std::map<unsigned int,MaterialProgramm * >::iterator it = programs.begin();
	while(it != programs.end())
	{
		MaterialProgramm * program = it->second;
		switchSource<<"\n\t\tcase "<<it->first<<" : return "<<program->name<<"(materialData);";
		functions<<program->getProcessedSource()<<"\n";
		it++;
	}
	switchSource<<"\n\t}\n";
	switchSource<<"}";
	return functions.str()+switchSource.str();
}
MaterialProgramManager::~MaterialProgramManager()
{
	std::map<unsigned int,MaterialProgramm * >::iterator it = programs.begin();
	while(it != programs.end())
	{
		delete it->second;
		it++;
	}
}

} /* namespace StingRay */
