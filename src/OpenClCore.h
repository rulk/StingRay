/*
 * OpenClCore.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef OPENCLCORE_H_
#define OPENCLCORE_H_
#include <CL/cl.h>

namespace StingRay {

class OpenClCore {

	cl_context context;
	cl_command_queue command_que;
	cl_device_id device_id;

	cl_platform_id platform_id;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	static OpenClCore * Instance;
	Image image;
	OpenClCore(int width,int height);

	virtual ~OpenClCore();
public:
	const int width, height;
	static OpenClCore * getInstance();
	static void init(int width,int height);
	static void destroy();
	clVectorBufferImpl* createBufferForStream(
			size_t numElements,size_t elementSize, SteramType type) {
		cl_mem_flags flags;
		switch (type) {
		case STREAM_READ:
			flags = CL_MEM_READ_ONLY;
			break;
		case STREAM_WRITE:
			flags = CL_MEM_WRITE_ONLY;
			break;
		default:THROW(0,"Unsupported Stream type sorry.");
		}
		clVectorBufferImpl * buffer = new clVectorBufferImpl(
				context, flags, command_que, elementSize,numElements);
		return buffer;

	}
	Image getRenderingImage();
	DeviceId getDeviceId()
	{
		return device_id;
	}
	Context getContext()
	{
		return context;
	}
	CommandQue getQue()
	{
		return command_que;
	}
	void flushQue()
	{
		clFlush(command_que);

	}
	void finishQue()
	{

		clFinish(command_que);
	}
	void initImageRendering();
	void dumpImage(std::string fname);


};

} /* namespace SimpleRayTracer */
#endif /* OPENCLCORE_H_ */
