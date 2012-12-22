/*
 * clVectorBufferImpl.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef CLVECTORBUFFERIMPL_H_
#define CLVECTORBUFFERIMPL_H_

#include <CL/cl.h>
#include "Exception.h"
namespace StingRay
{
class clVectorBufferImpl
{
	size_t allocatedSize;
	cl_context context;
	cl_mem_flags flags;
	cl_mem buffer;
	cl_command_queue command_queue;
	friend class OpenClKernel;
	void createBuffer()
	{
		cl_int ret;
		buffer = clCreateBuffer(context, flags,allocatedSize, NULL, &ret);
		//:TODO handle allocation fault
	}
	const cl_mem * getBuffer()const {return &buffer;}
public:
	clVectorBufferImpl(cl_context context,cl_mem_flags flags,cl_command_queue command_queue ,size_t maxSize =0)
						:allocatedSize(maxSize),context(context),flags(flags),command_queue(command_queue)
	{
		if(allocatedSize > 0 )
		{
			createBuffer();
		}
		else
			buffer = 0;
	}
	void write(const void * menBuffer,size_t size)
	{
		if(buffer == 0)
		{
			allocatedSize = size;
			createBuffer();
		}
		size_t toWrite = size;
		if(allocatedSize < toWrite)
			toWrite = allocatedSize;
		cl_int ret = clEnqueueWriteBuffer(command_queue, buffer, CL_TRUE, 0,
		            toWrite, menBuffer, 0, NULL, NULL);

		if(ret !=CL_SUCCESS)
			THROW(ret,"can;t write to device memory buffer");
	}
	size_t read(void * memBuffer,size_t size)
	{
		if(buffer == 0) return 0;

		size_t toRead = size;
		if(allocatedSize < toRead)toRead = allocatedSize;
		cl_int ret = clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0,
				toRead, memBuffer, 0, NULL, NULL);
		if(ret !=CL_SUCCESS)
			THROW(ret,"can;t read device memory buffer");
		return toRead;
	}
	~clVectorBufferImpl(){clReleaseMemObject(buffer);}
};
}

#endif /* CLVECTORBUFFERIMPL_H_ */
