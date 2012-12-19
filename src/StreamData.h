/*
 * StreamData.h
 *
 *  Created on: Dec 19, 2012
 *      Author: rulk
 */

#ifndef STREAMDATA_H_
#define STREAMDATA_H_
#include<vector>
#include <string>
template<class IMP>
class StreamData
{
protected:
	IMP data;
public:
	/*StreamData(const IMP & init) = 0;
	StreamData & operator = (const IMP & init) = 0;
	StreamData(const std::vector<std::string> & strings) =0;
	StreamData(void * ptr) = 0;
	*/
	void * getIMemoryPtr() const
	{
		return (void*)&data;
	}
	size_t getISize() const
	{
		return sizeof(IMP);
	}
	IMP geItData() const
	{
		return data;
	}
	void setIData(void * ptr)
	{
		data = *((IMP*)ptr);
	}

};


#endif /* STREAMDATA_H_ */
