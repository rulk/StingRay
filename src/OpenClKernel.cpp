/*
 * Kernel.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include "implementation.h"
namespace StingRay {
#define MAX_SOURCE_SIZE (0x100000)
OpenClKernel::OpenClKernel(const std::string & fileName,const std::string & kernelName)

{
	program = 0;
	kernel =0;
	this->kernelName = kernelName;
	//! TODO rewrite this horror
	  FILE *fp;
	    char *source_str;
	    size_t source_size;

	    fp = fopen(fileName.c_str(), "r");
	    if (!fp) {
	        THROW(2,"can't read program source");
	    }
	    source_str = (char*)malloc(MAX_SOURCE_SIZE);
	    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
	    fclose( fp );
	    cl_int ret;

	       // Create the OpenCL kernel
	    source= source_str;
	    free(source_str);
	    compiled = false;

}
void OpenClKernel::programFromSource(const std::string & append ,const std::string & prepend )
{
	std::string source;
	source = append+" "+this->source+" "+prepend;

	std::cout<<source<<std::endl;
	Context context = Core::getInstance()->getContext();
	DeviceId device = Core::getInstance()->getDeviceId();
	size_t size = source.size();
	const char * src = source.c_str();
	cl_int ret;
	program = clCreateProgramWithSource(context, 1, (const char **) &(src),
			(const size_t *) &size, &ret);

	// Build the program
	ret = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	char buildLog[10000];
	size_t rett;
	clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 10000,
			(void*) buildLog, &rett);
	if (ret != CL_SUCCESS)
	{

		THROW(0, buildLog);

	}
	else
	{
		std::cout << buildLog << std::endl;
	}
}
void OpenClKernel::createIKernel()
{
	cl_int ret;
	kernel = clCreateKernel(program, kernelName.c_str(), &ret);
}
void OpenClKernel::initDefaultArgs()
{
	if(!compiled) return;
	Image i = Core::getInstance()->getRenderingImage();
	setArg(0,&i);
}
void OpenClKernel::compileKernel()
{
	programFromSource();
	createIKernel();
	compiled = true;
	initDefaultArgs();
}

void OpenClKernel::run(CommandQue que,size_t * globalItemSize,size_t * localItemSize)
{
	if(!compiled)THROW(0,"You need to compile kernel before runing!");
	clFinish(que);
	cl_event event;
	cl_ulong t_start,t_finis;
	glFinish();
	Image img = Core::getInstance()->getRenderingImage();
	 clEnqueueAcquireGLObjects(que, 1, &img, 0, NULL, NULL);

	 cl_int ret = clEnqueueNDRangeKernel(que, kernel, 1, NULL,
	            globalItemSize, localItemSize, 0, NULL, &event);

	 if(ret != CL_SUCCESS)
		 THROW(ret,"clEnqueueNDRangeKernel return error");
	 clEnqueueReleaseGLObjects(que, 1, &img, 0, NULL, NULL);
	 clFinish(que);

	 clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(t_start),&t_start,NULL);
	 clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(t_finis),&t_finis,NULL);
	 double dt = t_finis - t_start;
	 dt /= 1000000.0;
	 std::cout<<"Kernel Execution time:"<<dt<<"ms"<<std::endl;
}
OpenClKernel::~OpenClKernel()
{
	 if(compiled)
	 {
		 clReleaseKernel(kernel);
	 	 clReleaseProgram(program);
	 }
}
} /* namespace SimpleRayTracer */
