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
namespace StingRay
{
class StreamData
{
public:

	virtual void * getIMemoryPtr() const = 0;
	virtual size_t getISize() const = 0;
	virtual void setIData(void * ptr) = 0;
	virtual ~StreamData(){};

};
}

#endif /* STREAMDATA_H_ */
