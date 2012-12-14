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
#include "VoidStream.h"
namespace StingRay
{

template <class vector> class VectorStream: protected VoidStream {
private:
	size_t maxElements;
	size_t validElements;

public:

	VectorStream(size_t maxElements,SteramType type):VoidStream(sizeof(vector)*maxElements,type),maxElements(maxElements),
									   validElements(0)
	{

	}
	~VectorStream()
	{

	}
	bool put(const vector & v)
	{
		if(validElements < maxElements && elemntBuffer != NULL)
		{
			putData<vector>(v);
			validElements++;
			return true;
		}
		return false;
	}
	bool replace(const vector & v,size_t position)
	{
		if(position < maxElements && validElements > position && elemntBuffer != NULL)
		{
			replaceData<vector>(v,position*sizeof(vector));
			return true;
		}
		return false;
	}
	bool get(size_t position,vector & result) const
	{
		if(position < validElements && elemntBuffer != NULL)
		{
			return getData< vector>(position*sizeof(vector),result);
		}
		return false;
	}

	//! Writes to associated implementation buffer aka writes to video memory
	void flush() const
	{
		flushData();
	}
	//! Reads associaed implementation buffer
	void sync()
	{
		syncData();
		validElements = validSize/sizeof(vector);
	}
	const Buffer * getBuffer()const {return buffer;}
	size_t getMaxElement() const{return maxElements;}
	size_t getValidElements() const { return validElements;}

	size_t getBufferByteSize() const {return maxElements*sizeof(vector);}
	size_t getValidBufferByteSize() const {return validElements*sizeof(vector);}
};

}
#endif /* VECTORSTREAM_H_ */
