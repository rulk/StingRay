/*
 * VoidStream.h
 *
 *  Created on: Dec 12, 2012
 *      Author: nrulk
 */

#ifndef VOIDSTREAM_H_
#define VOIDSTREAM_H_
#include "Exception.h"
namespace StingRay
{
class VoidStream
{
	size_t maxSize;
	size_t validSize;
	size_t elementSize;
	void * elemntBuffer;
	clVectorBufferImpl<char> * buffer;

public:
	VoidStream(size_t size, SteramType type, size_t elementSize = 1) :
		maxSize(size), validSize(0), buffer(buffer),elementSize(elementSize)
	{
		buffer = Core::getInstance()->createBufferForStream(maxSize, elementSize, type);
		elemntBuffer = malloc(maxSize);
		if (elemntBuffer == NULL)
			THROW(1, "can't allocate vector local memory buffer");
	}
	~VoidStream()
	{
		if (elemntBuffer != NULL)
			free(elemntBuffer);
	}
	template <class T> bool put(const T & data)
	{
		if(validSize+sizeof(T) < maxSize && elemntBuffer != NULL)
		{
			*((T*)(elemntBuffer+offset*elementSize))  = data;
			validSize+=off
			return true;
		}
		return false;
	}
	bool replace(const vector & v,size_t position)
	{
		if(position < maxElements && validElements > position && elemntBuffer != NULL)
		{
			elemntBuffer[position] = v;
			return true;
		}
		return false;
	}
	bool get(size_t position,vector & result) const
	{
		if(position < validElements && elemntBuffer != NULL)
		{
			result = elemntBuffer[position];
			return true;
		}
		return false;
	}
};
}


#endif /* VOIDSTREAM_H_ */
