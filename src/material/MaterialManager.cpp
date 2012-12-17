/*
 * MaterialManager.cpp
 *
 *  Created on: Dec 17, 2012
 *      Author: rulk
 */

#include "MaterialManager.h"

namespace StingRay {

MaterialManager::MaterialManager(const std::string & materialFolder, const std::string & programFolder):
		ConfigLoader(".material"),materialFolder(materialFolder)
{
	programManager = new MaterialProgramManager(programFolder);
	stream = NULL;
}

MaterialManager::~MaterialManager() {
	// TODO Auto-generated destructor stub
}
void MaterialManager::loadFile(const std::string & fileName)
{
	std::ifstream in(materialFolder+fileName, std::ios::binary);
	parseScript(in);
}
void MaterialManager::compile()
{
	std::map <std::string, ConfigNode*>::iterator it = m_scriptList.begin();
	size_t offset = 0;
	for(;it != m_scriptList.end();it++)
	{
		ConfigNode * programNode =  it->second->findChild("program");
		if(programNode == NULL)
			continue;

		std::string & programName = programNode->getValue(0);

		const MaterialProgramm * program = programManager->getProgram(programName);
		if(program == NULL) continue;
		Material * material = new Material(it->first,offset,this,program);
		size_t count = program->paramCount();
		for(size_t i=0;i<count;i++)
		{
			std::string paramName = program->getParamName(i);

			std::string type = program->getParamType(i);
			if(type == "float")
			{
				Real r = material->getParameterReal(paramName);
				stream->putData<Real>(r);
				offset += program->getParamOffset(i);
			}


		}


	}
}
Material * getMaterial(const std::string & name);
VoidStream * getCompiledStream();
} /* namespace StingRay */

