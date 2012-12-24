/*
 * MaterialProgramm.h
 *
 *  Created on: Dec 11, 2012
 *      Author: nrulk
 */

#ifndef MATERIALPROGRAMM_H_
#define MATERIALPROGRAMM_H_
#include <string>
#include <map>
namespace StingRay
{
#define INVALID_ID 999
struct MaterialProgramParam
{
	std::string type;
	std::string name;
	size_t id;
	size_t offset;
	size_t size;
	bool isNaN;

};
class MaterialProgram
{
	std::string name;
	std::string processedSource;
	size_t paramsByteSize;
	unsigned int id;
	std::map<unsigned int,MaterialProgramParam> params;
	std::map<std::string,unsigned int> paramNameId;
	MaterialProgram(const std::string & name,const std::string & filename,unsigned int id);
	virtual ~MaterialProgram();
	friend class MaterialProgramManager;
public:
	size_t getParamCount() const;
	size_t getParamTotalLength() const;
	size_t getParamOffset(unsigned int id) const;
	size_t getParamOffset(const std::string & name) const;
	std::string getParamName(unsigned int id) const;
	std::string getParamType(unsigned int id) const;
	std::string getProcessedSource() const;
	unsigned int getParamId(const std::string & name) const;
	unsigned int getId()const {return id;}
	const MaterialProgramParam & getById(unsigned int id)const;


private:
	void loadFile(const std::string & fname);
	void processSource();

};
}
#endif /* MATERIALPROGRAMM_H_ */
