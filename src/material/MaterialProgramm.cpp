/*
 * MaterialProgramm.cpp
 *
 *  Created on: Dec 11, 2012
 *      Author: nrulk
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include "MaterialProgramm.h"
#include "StringUtils.h"
#include "Exception.h"
namespace StingRay
{

MaterialProgramm::MaterialProgramm(const std::string & name,const std::string & filename)
{
	this->name = name;
	paramsByteSize = 0;
	loadFile(filename);
	processSource();


}
void MaterialProgramm::loadFile(const std::string & fname)
{
	std::ifstream source(fname.c_str());
	std::string line;

	std::stringstream sourceStream;
	sourceStream<<"float4 "<<name<<"()\n{\n";
	if(source.is_open())
	{
		 while ( source.good() )
		 {
			 std::getline (source,line);
			 sourceStream<<line;

		 }
		 source.close();
	}
	else
	{
		std::cout<<"failed to open file:"<<fname<<std::endl;
		THROW(0,"failed to load program:"+fname);
	}
	sourceStream<<"\n}";

	processedSource =  sourceStream.str();

}
void MaterialProgramm::processSource()
{
	size_t cur_pos = 0;
	size_t start_pos = std::string::npos;
	size_t end_pos = std::string::npos;
	paramsByteSize = 0;
	size_t fragment_start_pos = 0;
	std::stringstream source;
	size_t paramCounter = 0;
	while(1)
	{
		if (start_pos != std::string::npos)
		{
			end_pos = processedSource.find(";",cur_pos);
			cur_pos = end_pos;
		}
		else
		{

			start_pos = processedSource.find("IN",cur_pos);
			cur_pos = start_pos;
		}


		if(start_pos != std::string::npos && end_pos != std::string::npos)
		{

			MaterialProgramParam param;
			size_t open = processedSource.find("(",start_pos);
			size_t comma1 = processedSource.find(",",open);

			param.type = processedSource.substr(open+1,comma1-open-1);
			param.type = trim(param.type);

			size_t close = processedSource.find(")",comma1);
			param.name = processedSource.substr(comma1+1,close-comma1-1);
			param.name = trim(param.name);
			param.id = paramCounter;
			param.offset = paramsByteSize;
			cur_pos = close;
			param.isNaN = false;

			param.size = getTypeSize(param.type);
			if(param.size == 0)
			{
				THROW(0,"Unknown type:"+param.type+"in program:"+name);
			}
			paramsByteSize +=param.size;
			params[paramCounter] = param;
			paramNameId[param.name] = param.id;
			source<<processedSource.substr(fragment_start_pos,start_pos-fragment_start_pos);
			source<<"\t"<<param.type<<" "<<param.name<<" = *(("<<param.type<<"*)(materialData+"<<param.offset<<"));\n";
			fragment_start_pos = end_pos+1;
			paramCounter ++;
			start_pos = std::string::npos;
			end_pos = std::string::npos;

		}
		else if(start_pos == std::string::npos && end_pos == std::string::npos)
			break;

	}
	source<<processedSource.substr(fragment_start_pos,processedSource.length());
	processedSource = source.str();

}
size_t MaterialProgramm::paramCount() const
{
	return params.size();
}
size_t MaterialProgramm::paramTotalLength() const
{
	return paramsByteSize;
}
const MaterialProgramParam & MaterialProgramm::getById(unsigned int id) const
{
	std::map<unsigned int,MaterialProgramParam>::const_iterator it = params.find(id);
	if(it != params.end())
	{
		return it->second;
	}
	else
	{
		THROW(0,"Can't find parameter by id in program:"+name);
	}
}
size_t MaterialProgramm::getParamOffset(unsigned int id) const
{
	MaterialProgramParam param = getById(id);
	if(!param.isNaN) return param.offset;
	return 0;
}
size_t MaterialProgramm::getParamOffset(const std::string & name) const
{
	MaterialProgramParam param = getById(getParamId(name));
	if(!param.isNaN) return param.offset;
	return 0;
}
std::string  MaterialProgramm::getParamName(unsigned int id) const
{
	MaterialProgramParam param = getById(id);
	if(!param.isNaN) return param.name;
	return 0;
}
std::string MaterialProgramm::getProcessedSource() const
{
	return processedSource;
}
unsigned int MaterialProgramm::getParamId(const std::string & name) const
{
	std::map<std::string,unsigned int>::const_iterator it = paramNameId.find(name);
	if(it != paramNameId.end())
		return it->second;
	return INVALID_ID;
}
MaterialProgramm::~MaterialProgramm()
{
	// TODO Auto-generated destructor stub
}
}
