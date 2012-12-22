/*
 * OpenClImpl.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef OPENCLIMPL_H_
#define OPENCLIMPL_H_
#include <CL/cl.h>
#include <string>
// Generating diffrent kinds of native vecors
#include "Vec.h"

#include "StreamData.h"
// Mainly for Material compatability to support single value constants
#define DIMENSION 1
#define STREAM_VEC_CLASS_NAME StreamVec1
#include "StreamVec.h"
#undef DIMENSION
#undef STREAM_VEC_CLASS_NAME

#define DIMENSION 2
#define STREAM_VEC_CLASS_NAME StreamVec2
#include "StreamVec.h"
#undef DIMENSION
#undef STREAM_VEC_CLASS_NAME

#define DIMENSION 3
#define STREAM_VEC_CLASS_NAME StreamVec3
#include "StreamVec.h"
#undef DIMENSION
#undef STREAM_VEC_CLASS_NAME

#define DIMENSION 4
#define STREAM_VEC_CLASS_NAME StreamVec4
#include "StreamVec.h"
#undef DIMENSION
#undef STREAM_VEC_CLASS_NAME
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

inline Vector4Impl Vector4I(Real x, Real y, Real z, Real w)
{
	Vector4Impl vec;
	vec.x = x, vec.y = y;
	vec.z = z;
	vec.w = w;
	return vec;
}
inline Vector3Impl Vector3I(Real x, Real y, Real z)
{
	Vector3Impl vec;
	vec.x = x, vec.y = y;
	vec.z = z;
	return vec;
}
inline Vector2Impl Vector2I(Real x, Real y)
{
	Vector2Impl vec;
	vec.x = x, vec.y = y;
	return vec;
}
inline Real RealI(const std::string & x)
{
	return atof(x.c_str());
}
inline Vector4Impl Vector4I(const std::string & x, const std::string & y,
		const std::string & z, const std::string & w)
{
	Vector4Impl vec;
	vec.x = RealI(x), vec.y = RealI(y);
	vec.z = RealI(z);
	vec.w = RealI(w);
	return vec;
}
inline Vector3Impl Vector3I(const std::string x, const std::string & y,
		const std::string & z)
{
	Vector3Impl vec;
	vec.x = RealI(x), vec.y = RealI(y);
	vec.z = RealI(z);
	return vec;
}
inline Vector2Impl Vector2I(const std::string & x, const std::string & y)
{
	Vector2Impl vec;
	vec.x = RealI(x), vec.y = RealI(x);
	return vec;
}

typedef StreamVec1<float, cl_float> Fvec1;
typedef StreamVec2<float, cl_float2> Fvec2;
typedef StreamVec3<float, cl_float3> Fvec3;
typedef StreamVec4<float, cl_float4> Fvec4;

typedef StreamVec1<int, cl_int> Ivec1;
typedef StreamVec2<int, cl_int2> Ivec2;
typedef StreamVec3<int, cl_int3> Ivec3;
typedef StreamVec4<int, cl_int4> Ivec4;

typedef StreamVec1<unsigned int, cl_uint>  uIvec1;
typedef StreamVec2<unsigned int, cl_uint2> uIvec2;
typedef StreamVec3<unsigned int, cl_uint3> uIvec3;
typedef StreamVec4<unsigned int, cl_uint4> uIvec4;

inline size_t getTypeSize(const std::string & type)
{
	if (type == "float")
		return sizeof(cl_float);
	else if (type == "float2")
		return sizeof(cl_float2);
	else if (type == "float3")
		return sizeof(cl_float3);
	else if (type == "float4")
		return sizeof(cl_float4);
	else if (type == "int")
		return sizeof(cl_int);
	else if (type == "int2")
		return sizeof(cl_int2);
	else if (type == "int3")
		return sizeof(cl_int3);
	else if (type == "int4")
		return sizeof(cl_int4);


	else if (type == "uint")
		return sizeof(cl_uint);
	else if (type == "uint2")
		return sizeof(cl_uint2);
	else if (type == "uint3")
		return sizeof(cl_uint3);
	else if (type == "uint4")
		return sizeof(cl_uint4);
	return 0;
}

inline StreamData* constructTypeFromStrings(const std::string & type,const std::vector<std::string>& values)
{
	if (type == "float")
		return new Fvec1(values);
	else if (type == "float2")
		return new Fvec2(values);
	else if (type == "float3")
		return new Fvec3(values);
	else if (type == "float4")
		return new Fvec4(values);

	else if (type == "int")
		return new Ivec1(values);
	else if (type == "int2")
		return new Ivec2(values);
	else if (type == "int3")
		return new Ivec3(values);
	else if (type == "int4")
		return new Ivec4(values);

	else if (type == "uint")
		return new uIvec1(values);
	else if (type == "uint2")
		return new uIvec2(values);
	else if (type == "uint3")
		return new uIvec3(values);
	else if (type == "uint4")
		return new uIvec4(values);
	return 0;
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
