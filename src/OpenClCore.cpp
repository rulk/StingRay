/*
 * OpenClCore.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */
#include <stdio.h>
#include <stdlib.h>

#include <GL/glxew.h>
#include <CL/cl_gl.h>
#include "implementation.h"

namespace StingRay {
OpenClCore * OpenClCore::Instance = NULL;
void OpenClCore::init(int width,int height)
{
	Instance = new OpenClCore(width,height);
}
 void OpenClCore::destroy()
{
	if(Instance != NULL)
		delete Instance;
	Instance = NULL;
}
 OpenClCore * OpenClCore::getInstance()
 {
	 if(Instance == NULL)
		 THROW(0,"Attempt to acsess OpenCl core object before initialization!");
	 return Instance;
 }
OpenClCore::OpenClCore(int width,int height):width(width),height(height) {

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
		    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_ALL, 1,
		            &device_id, &ret_num_devices);

		    cl_context_properties properties[] = {
		       CL_GL_CONTEXT_KHR, (cl_context_properties) glXGetCurrentContext(),
		       CL_GLX_DISPLAY_KHR, (cl_context_properties) glXGetCurrentDisplay(),
		       CL_CONTEXT_PLATFORM, (cl_context_properties) platform_id,
		       0};
		    // Create an OpenCL context
		     context = clCreateContext( properties, 1, &device_id, NULL, NULL, &ret);

		    // Create a command queue
		     command_que = clCreateCommandQueue(context, device_id, 0, &ret);
		     image = NULL;

}
void OpenClCore::initImageRendering()
{
	cl_int  ret = CL_SUCCESS;
	cl_image_format format;
	format.image_channel_order = CL_RGBA;
	format.image_channel_data_type = CL_UNSIGNED_INT8;
	//image = clCreateImage2D(context,CL_MEM_WRITE_ONLY,&format,width,height,0,NULL,&ret);
	image =  clCreateFromGLBuffer(context,CL_MEM_WRITE_ONLY,GL_FRONT,&ret);
	if(ret != CL_SUCCESS || image == NULL)
		THROW(0,"Can't create image bufer");
}
void OpenClCore::dumpImage(std::string fname)
{
	/*FreeImage_Initialise();
	BYTE * pixels =(BYTE*) malloc(4*width*height);
	const size_t origin[3] = {0,0,0};
	const size_t reg[3] = {width,height,1};
	cl_int ret = clEnqueueReadImage(command_que,image,CL_TRUE,origin,reg,0,0,pixels,0,NULL,NULL);
	if(ret != CL_SUCCESS)
		THROW(0,"can't read device image sorry");
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, width, height, width*4 , 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, false);

		std::cout << "Saving screenshot: " << fname << "\n";

		FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
		free(pixels);
		FreeImage_DeInitialise();
		*/
}
Image OpenClCore::getRenderingImage()
{
	return image;
}
OpenClCore::~OpenClCore() {
	// TODO Auto-generated destructor stub
}

} /* namespace SimpleRayTracer */
