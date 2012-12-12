/*
 * VectorStream.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef VECTORSTREAM_H_
#define VECTORSTREAM_H_
#include <stdio.h>
#include <stdlib.h>
#include "Exception.h"
namespace StingRay
{

template <class vector, class implBuffer> class VectorStream {
private:
	size_t maxElements;
	size_t validElements;
	vector * elemntBuffer;
	Buffer * buffer;



public:

	VectorStream(size_t maxElements,SteramType type):maxElements(maxElements),
									   validElements(0),buffer(buffer)
	{
		buffer = Core::getInstance()->createBufferForStream(maxElements,sizeof(vector),type);
		elemntBuffer = (vector*)malloc(sizeof(vector)*maxElements);
		if(elemntBuffer == NULL)
			THROW(1,"can't allocate vector local memory buffer");
	}
	~VectorStream()
	{
		if(elemntBuffer != NULL)
			free(elemntBuffer);
	}

	bool put(const vector & v)
	{
		if(validElements < maxElements && elemntBuffer != NULL)
		{
			elemntBuffer[validElements]  = v;
			validElements++;
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

	//! Writes to associated implementation buffer aka writes to video memory
	void flush() const
	{
		buffer->write(elemntBuffer,getValidElements(),sizeof(vector));
	}
	//! Reads associaed implementation buffer
	void sync()
	{
		validElements = buffer->read(elemntBuffer,maxElements,sizeof(vector));
	}
	const implBuffer * getBuffer()const {return buffer;}
	size_t getMaxElement() const{return maxElements;}
	size_t getValidElements() const { return validElements;}

	size_t getBufferByteSize() const {return maxElements*sizeof(vector);}
	size_t getValidBufferByteSize() const {return validElements*sizeof(vector);}
};

}
#endif /* VECTORSTREAM_H_ */
