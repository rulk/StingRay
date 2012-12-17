/*
 * MaterialProgramManager.h
 *
 *  Created on: Dec 12, 2012
 *      Author: nrulk
 */

#ifndef MATERIALPROGRAMMANAGER_H_
#define MATERIALPROGRAMMANAGER_H_
#include "MaterialProgramm.h"
namespace StingRay
{

class MaterialProgramManager
{
	std::string programPath;
	int progRamIdCounter;
	std::string programExtension;
	std::map<unsigned int,MaterialProgramm * > programs;
	std::map<std::string, unsigned int> programNameToId;

	MaterialProgramm *  loadProgram(const std::string & name);
	void buildSwitchSource(std::stringstream & out);
public:
	MaterialProgramManager(const std::string & programPath, const std::string & programExtension = "cl");

	const MaterialProgramm * getProgram(const std::string & name);
	const MaterialProgramm * getProgram(const std::string & name,const std::string & fullPath );
	const MaterialProgramm * getProgramById(unsigned int id);

	std::string buildSource();
	virtual ~MaterialProgramManager();
};

} /* namespace StingRay */
#endif /* MATERIALPROGRAMMANAGER_H_ */
