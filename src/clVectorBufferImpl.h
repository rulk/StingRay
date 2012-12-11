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
namespace SimpleRayTracer
{
template<class vectro> class clVectorBufferImpl
{
	size_t allocatedElements;
	cl_context context;
	cl_mem_flags flags;
	cl_mem buffer;
	cl_command_queue command_queue;
	friend class OpenClKernel;
	void createBuffer()
	{
		cl_int ret;
		buffer = clCreateBuffer(context, flags,
				allocatedElements * sizeof(vectro), NULL, &ret);
		//:TODO handle allocation fault
	}
	const cl_mem * getBuffer()const {return &buffer;}
public:
	clVectorBufferImpl(cl_context context,cl_mem_flags flags,cl_command_queue command_queue ,size_t elementNum = 0)
						:context(context),flags(flags),command_queue(command_queue)
	{
		allocatedElements = 0;
		if(elementNum > 0)
		{
			allocatedElements = elementNum;
			createBuffer();

		}
		else
			buffer = 0;
	}
	void write(const void * menBuffer,size_t validElements)
	{
		if(buffer == 0)
		{
			allocatedElements = validElements;
			createBuffer();
		}
		size_t toWrite = validElements;
		if(allocatedElements < toWrite)
			toWrite = allocatedElements;
		cl_int ret = clEnqueueWriteBuffer(command_queue, buffer, CL_TRUE, 0,
		            toWrite * sizeof(vectro), menBuffer, 0, NULL, NULL);

		if(ret !=CL_SUCCESS)
			THROW(ret,"can;t write to device memory buffer");
	}
	size_t read(void * memBuffer,size_t validElements)
	{
		if(buffer == 0) return 0;
		size_t toRead = validElements;
		if(allocatedElements < toRead)toRead = allocatedElements;
		cl_int ret = clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0,
				toRead * sizeof(vectro), memBuffer, 0, NULL, NULL);
		if(ret !=CL_SUCCESS)
			THROW(ret,"can;t read device memory buffer");
		return toRead;
	}
	~clVectorBufferImpl(){clReleaseMemObject(buffer);}
};
}

#endif /* CLVECTORBUFFERIMPL_H_ */
