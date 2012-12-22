/*
 * OpenClCore.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */
#include <stdio.h>
#include <stdlib.h>
//#include <GL/glew.h>
//#include <GL/glxew.h>
//#include <CL/cl_gl.h>
#include "FreeImage.h"
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

	cl_uint ret_num_platforms;
	cl_platform_id platforms[10];
	cl_int ret = clGetPlatformIDs(10, platforms, &ret_num_platforms);
	char str[500];
	size_t strl;
	for(cl_uint i=0;i<ret_num_platforms;i++)
	{
		clGetPlatformInfo(platforms[i],CL_PLATFORM_NAME,500,(void*)str,&strl);
		std::cout<<"Found platform:"<<str<<" extensions:";
		clGetPlatformInfo(platforms[i],CL_PLATFORM_EXTENSIONS,500,(void*)str,&strl);
		std::cout<<str<<std::endl;
		platform_id = platforms[i];
	}

	cl_device_id ids[5];
	cl_uint ret_num_devices;
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 5, ids,
			&ret_num_devices);
	for(cl_uint i=0;i<ret_num_devices;i++)
	{
		cl_device_type type;
		size_t returned;
		clGetDeviceInfo(ids[i],CL_DEVICE_TYPE,sizeof(cl_device_type),&type,&returned);
		if(type == CL_DEVICE_TYPE_CPU)
		{
			device_id = ids[i];
			std::cout<<"Device :"<<ids[i]<<" type CPU"<<std::endl;
		}
		if(type == CL_DEVICE_TYPE_GPU)
		{
			device_id = ids[i];
			std::cout<<"Device :"<<ids[i]<<" type GPU"<<std::endl;
			break;
		}
	}

	/*cl_context_properties properties[] = { CL_GL_CONTEXT_KHR,
			(cl_context_properties) glXGetCurrentContext(), CL_GLX_DISPLAY_KHR,
			(cl_context_properties) glXGetCurrentDisplay(), CL_CONTEXT_PLATFORM,
			(cl_context_properties) platform_id, 0 };*/
	// Create an OpenCL context
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

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
	/*glGenTextures(1, &color_tex);
	glBindTexture(GL_TEXTURE_2D, color_tex);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//NULL means reserve texture memory, but texels are undefined
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, NULL);
	//-------------------------
	glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	//Attach 2D texture to this FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
			GL_TEXTURE_2D, color_tex, 0);
	glFlush();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);*/
	image = clCreateImage2D(context,CL_MEM_WRITE_ONLY,&format,width,height,0,NULL,&ret);
	//image =  clCreateFromGLTexture(context,CL_MEM_WRITE_ONLY,GL_TEXTURE_2D,0,color_tex,&ret);
	if(ret != CL_SUCCESS || image == NULL)
		THROW(0,"Can't create image bufer");
}
void OpenClCore::dumpImage(std::string fname)
{
	/*glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, fb);
	glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
	glBlitFramebufferEXT(0,0,width,height,0,0,width,height,GL_COLOR_BUFFER_BIT,GL_NEAREST);

	*/
	FreeImage_Initialise();
	BYTE * pixels =(BYTE*) malloc(4*width*height);
	if(pixels == NULL)
		THROW(0,"malloc returned NULL");
	const size_t origin[3] = {0,0,0};
	const size_t reg[3] = {width,height,1};
	clFinish(command_que);
	cl_int ret = clEnqueueReadImage(command_que,image,CL_TRUE,origin,reg,
									   0,0,pixels,0,NULL,NULL);

	if(ret != CL_SUCCESS)
		THROW(ret,"can't read device image sorry");
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, width, height,
			width*4 , 32, 0xff000000, 0xff000000, 0xff000000, false);

	std::cout << "Saving screenshot: " << fname << "\n";

	FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
	//free(pixels);
	FreeImage_DeInitialise();

}
Image OpenClCore::getRenderingImage()
{
	return image;
}
OpenClCore::~OpenClCore() {
	// TODO Auto-generated destructor stub
}

} /* namespace SimpleRayTracer */
