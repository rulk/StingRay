/*
 * Kernel.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef KERNEL_H_
#define KERNEL_H_
#include <string>
namespace SimpleRayTracer {

class OpenClKernel
{


	cl_program program;
	cl_kernel kernel;
	bool bProgramOwner;
	cl_int setArgs(cl_uint arg_index,size_t arg_size,	const void *arg_value)
	{
			return clSetKernelArg(kernel,arg_index,arg_size,arg_value);

	}
	cl_program getCLProgramm(){return program;}
public:
	size_t setArg(size_t index,const RealStream * stream)
	{
		return setArgs(index,sizeof(cl_mem),stream->getBuffer()->getBuffer());
	}
	size_t setArg(size_t index,const Vector2ImplStream * stream)
	{
			return setArgs(index,sizeof(cl_mem),stream->getBuffer()->getBuffer());
	}
	size_t setArg(size_t index,const Vector4ImplStream * stream)
	{
			return setArgs(index,sizeof(cl_mem),stream->getBuffer()->getBuffer());
	}
	size_t setArg(size_t index,const Image * img)
	{
		return clSetKernelArg(kernel,index,sizeof(cl_mem),img);
	}
	size_t setArg(size_t index,int i)
	{
		return clSetKernelArg(kernel,index,sizeof(cl_int),(void *)&i);
	}


public:
	OpenClKernel(const std::string & fileName,const std::string & kernelName = "main");
	OpenClKernel(Program program,const std::string & kernelName = "main");

	void run(CommandQue que,size_t *globalItemSize,size_t *localItemSize);

	virtual ~OpenClKernel();
};

} /* namespace SimpleRayTracer */
#endif /* KERNEL_H_ */
