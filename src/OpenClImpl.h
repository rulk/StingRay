/*
 * OpenClImpl.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef OPENCLIMPL_H_
#define OPENCLIMPL_H_
#include <CL/cl.h>
namespace SimpleRayTracer
{
	typedef cl_context Context;
	typedef cl_program Program;
	typedef cl_device_id DeviceId;
	typedef cl_command_queue CommandQue;

	typedef cl_float Real;
	typedef cl_float4 Vector4Impl;
	typedef cl_float3 Vector3Impl;
	typedef cl_float2 Vector2Impl;

	inline Vector4Impl Vector4I(Real x,Real y,Real z,Real w)
	{
		Vector4Impl vec;
		vec.x = x,vec.y = y;vec.z=z;vec.w =w;
		return vec;
	}
	inline Vector3Impl Vector3I(Real x,Real y,Real z)
		{
			Vector3Impl vec;
			vec.x = x,vec.y = y;vec.z=z;
			return vec;
		}
	inline Vector2Impl Vector2I(Real x,Real y)
		{
			Vector2Impl vec;
			vec.x = x,vec.y = y;
			return vec;
		}
	typedef cl_mem Image;
}
#include "clVectorBufferImpl.h"
namespace SimpleRayTracer
{
	typedef clVectorBufferImpl<cl_float> RealBuffer;
	typedef clVectorBufferImpl<cl_float2> Vector2ImplBuffer;
	typedef clVectorBufferImpl<cl_float3> Vector3ImplBuffer;
	typedef clVectorBufferImpl<cl_float4> Vector4ImplBuffer;
}
#include "OpenClCore.h"
namespace SimpleRayTracer
{
	typedef OpenClCore Core;
}
#include "VectorStream.h"
namespace SimpleRayTracer
{
	typedef VectorStream<cl_float,RealBuffer> RealStream;
	typedef VectorStream<cl_float2,Vector2ImplBuffer> Vector2ImplStream;
	typedef VectorStream<cl_float3,Vector3ImplBuffer> Vector3ImplStream;
	typedef VectorStream<cl_float4,Vector4ImplBuffer> Vector4ImplStream;
}
#include "OpenClKernel.h"
namespace SimpleRayTracer
{
	typedef OpenClKernel Kernel;
}
#endif /* OPENCLIMPL_H_ */
