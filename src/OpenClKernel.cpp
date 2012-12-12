/*
 * Kernel.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */
#include <CL/cl.h>
#include "implementation.h"
namespace StingRay {
#define MAX_SOURCE_SIZE (0x100000)
OpenClKernel::OpenClKernel(const std::string & fileName,const std::string & kernelName)

{
	Context context = Core::getInstance()->getContext();
	DeviceId device = Core::getInstance()->getDeviceId();
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
	    program = clCreateProgramWithSource(context, 1,
	               (const char **)&source_str, (const size_t *)&source_size, &ret);

	       // Build the program
	    ret = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	    char buildLog[10000];
	    size_t rett;
	    clGetProgramBuildInfo(program,device,CL_PROGRAM_BUILD_LOG,10000,(void*)buildLog,&rett);
	    if(ret!=CL_SUCCESS)
	    {

	    	THROW(0,buildLog);

	    }
	    else
	    {
	    	std::cout<<buildLog<<std::endl;
	    }
	       // Create the OpenCL kernel
	    kernel = clCreateKernel(program, kernelName.c_str(), &ret);
	    free(source_str);
	    bProgramOwner = true;

}
OpenClKernel::OpenClKernel(Program program,const std::string & kernelName ):
				program(program)
{
	bProgramOwner = false;
	 cl_int ret;
	 kernel = clCreateKernel(program, kernelName.c_str(), &ret);
}
void OpenClKernel::run(CommandQue que,size_t * globalItemSize,size_t * localItemSize)
{
	clFinish(que);
	cl_event event;
	cl_ulong t_start,t_finis;


	 cl_int ret = clEnqueueNDRangeKernel(que, kernel, 1, NULL,
	            globalItemSize, localItemSize, 0, NULL, &event);

	 if(ret != CL_SUCCESS)
		 THROW(ret,"clEnqueueNDRangeKernel return error");

	 clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(t_start),&t_start,NULL);
	 clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(t_finis),&t_finis,NULL);
	 double dt = t_finis - t_start;
	 dt /= 1000000.0;
	 std::cout<<"Kernel Execution time:"<<dt<<"ms"<<std::endl;
}
OpenClKernel::~OpenClKernel()
{
	 clReleaseKernel(kernel);
	 if(bProgramOwner) clReleaseProgram(program);
}
} /* namespace SimpleRayTracer */
