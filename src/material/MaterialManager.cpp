/*
 * MaterialManager.cpp
 *
 *  Created on: Dec 17, 2012
 *      Author: rulk
 */
#include <fstream>
#include "MaterialManager.h"
#include "Material.h"
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
	std::ifstream in((materialFolder+fileName).c_str(), std::ios::binary);
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
		{
			std::cout<<"Material "<<it->first<<"must specify program .. will not be rendered"<<std::endl;
			continue;
		}

		const std::string & programName = programNode->getValue(0);

		const MaterialProgram * program = programManager->getProgram(programName);
		if(program == NULL) continue;
		Material * material = new Material(it->second,offset,this,program);
		size_t count = program->getParamCount();
		bool materialOk = true;
		for(size_t i=0;i<count;i++)
		{
			std::string paramName = program->getParamName(i);
			if(!material->hasParameter(paramName))
			{
				std::cout<<"Material "<<it->first<<" has not specified parameter "<<program->getParamType(i)<<" "<<paramName<<" .. will not be rendered"<<std::endl;
				materialOk = false;
				break;
			}

		}
		if(materialOk)
		{
			materials[material->getName()] = material;
			offset+=program->getParamTotalLength();
		}
	}

	stream = new VoidStream(offset,STREAM_READ);

	// now iterate over good materials
	MaterialMap::iterator mat = materials.begin();
	for(;mat!= materials.end();mat++)
	{
		Material * material = mat->second;
		size_t count = material->program->getParamCount();
		for(size_t i=0;i<count;i++)
		{
			StreamData * data = material->getParameter(i);
			stream->putStreamData(*data);
		}

	}
	stream->flushData();
}
Material * MaterialManager::getMaterial(const std::string & name)
{
	MaterialMap::iterator mat = materials.find(name);
	if(mat != materials.end())
	{
		return mat->second;
	}
	return NULL;
}
VoidStream * MaterialManager::getCompiledStream()
{
	if(stream == NULL)
		compile();
	return stream;
}
} /* namespace StingRay */

