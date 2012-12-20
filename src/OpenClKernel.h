/*
 * Kernel.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef KERNEL_H_
#define KERNEL_H_
#include <string>
namespace StingRay {
#define KERNEL_IMAGE_ARG 0
#define KERNEL_CAMERA_ARG 1
class OpenClKernel
{

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
	size_t setArg(size_t index,const VoidStream * stream)
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
	OpenClKernel(const std::string & fileName,const std::string & kernelName = "renderKernel");

	void run(CommandQue que,size_t *globalItemSize,size_t *localItemSize);
	virtual void compileKernel();

	virtual ~OpenClKernel();
protected:
	cl_program program;
	cl_kernel kernel;
	std::string source;
	std::string kernelName;
	bool compiled;
	cl_int setArgs(cl_uint arg_index, size_t arg_size, const void *arg_value)
	{
		return clSetKernelArg(kernel, arg_index, arg_size, arg_value);

	}
	cl_program getCLProgramm()
	{
		return program;
	}
	void initDefaultArgs();
	void programFromSource(const std::string & append = "",const std::string & prepend ="");
	void createIKernel();
};

} /* namespace SimpleRayTracer */
#endif /* KERNEL_H_ */
