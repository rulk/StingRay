/*
 * OpenClImpl.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef OPENCLIMPL_H_
#define OPENCLIMPL_H_
#include <CL/cl.h>
namespace StingRay
{
	typedef cl_context Context;
	typedef cl_program Program;
	typedef cl_device_id DeviceId;
	typedef cl_command_queue CommandQue;

	typedef cl_char Char;

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
namespace StingRay
{
	typedef clVectorBufferImpl Buffer;
}
#include "OpenClCore.h"
namespace StingRay
{
	typedef OpenClCore Core;
}
#include "VectorStream.h"
namespace StingRay
{
	typedef VectorStream<cl_float> RealStream;
	typedef VectorStream<cl_float2> Vector2ImplStream;
	typedef VectorStream<cl_float3> Vector3ImplStream;
	typedef VectorStream<cl_float4> Vector4ImplStream;
}
#include "OpenClKernel.h"
namespace StingRay
{
	typedef OpenClKernel Kernel;
}
#endif /* OPENCLIMPL_H_ */
