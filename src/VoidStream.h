/*
 * VoidStream.h
 *
 *  Created on: Dec 12, 2012
 *      Author: nrulk
 */

#ifndef VOIDSTREAM_H_
#define VOIDSTREAM_H_
#include <string.h>
#include "Exception.h"
namespace StingRay
{
class VoidStream
{
protected:
	size_t maxSize;
	size_t validSize;
	void * elemntBuffer;
	Buffer * buffer;

public:
	VoidStream(size_t size, SteramType type) :
			maxSize(size), validSize(0), buffer(buffer)
	{
		buffer = Core::getInstance()->createBufferForStream(maxSize, type);
		elemntBuffer = malloc(maxSize);
		if (elemntBuffer == NULL)
			THROW(1, "can't allocate vector local memory buffer");
	}
	virtual ~VoidStream()
	{
		if (elemntBuffer != NULL)
			free(elemntBuffer);
	}
	template<class T> bool putData(const T & data)
	{
		if (validSize + sizeof(T) <= maxSize && elemntBuffer != NULL)
		{
			*((T*) (((char*)elemntBuffer) + validSize)) = data;
			validSize += sizeof(T);
			return true;
		}
		return false;
	}
	/**
	 * Use with extreme care if you rewrite some data not probably alighn you will get junk
	 */
	template<class T> bool replaceData(const T & data, size_t offset)
	{
		if (offset + sizeof(T) <= maxSize && elemntBuffer != NULL)
		{
			*((T*) (((char*)elemntBuffer) + offset)) = data;
			return true;
		}
		return false;
	}
	template<class T> bool getData(size_t offset, T & result) const
	{
		if (offset + sizeof(T) <= validSize && elemntBuffer != NULL)
		{
			result = *((T*) (((char*)elemntBuffer) + offset));
			return true;
		}
		return false;
	}
	bool putData(const void * data, size_t size)
	{
		if (validSize + size <= maxSize && elemntBuffer != NULL)
		{
			memcpy(((char*)elemntBuffer) + validSize, data, size);
			validSize += size;
			return true;
		}
		return false;

	}
	bool replaceData(const void * data, size_t size, size_t offset)
	{
		if (offset + size <= maxSize && elemntBuffer != NULL)
		{
			memcpy(((char*)elemntBuffer) + offset, data, size);
			return true;
		}
		return false;
	}
	bool getData(size_t offset, void * data, size_t size)
	{
		if (offset + size <= validSize && elemntBuffer != NULL)
		{
			memcpy(data, (((char*)elemntBuffer) + offset), size);
			return true;
		}
		return false;
	}
	bool putStreamData(const StreamData & data)
	{
		return putData(data.getIMemoryPtr(), data.getISize());
	}
	bool replaceStreamData(const StreamData & data,size_t offset)
	{
		return replaceData(data.getIMemoryPtr(), data.getISize(),offset);
	}
	bool getStreamData(size_t offset, StreamData & data)
	{
		if (offset + data.getISize() <= validSize && elemntBuffer != NULL)
		{
			data.setIData((((char*)elemntBuffer) + offset));
			return true;
		}
		return false;
	}

	void flushData() const
	{
		buffer->write(elemntBuffer, validSize);
	}
	//! Reads associaed implementation buffer
	void syncData()
	{
		validSize = buffer->read(elemntBuffer, maxSize);
	}
	const Buffer * getBuffer()const {return buffer;}
};
}

#endif /* VOIDSTREAM_H_ */
