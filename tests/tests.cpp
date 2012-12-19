/*
 * tests.cpp
 *
 *  Created on: Dec 19, 2012
 *      Author: rulk
 */

#include <CL/cl.h>
#ifdef UNIT_TESTS

#include "Vec.h"

#include "StreamData.h"
#define DIMENSION 1
#define STREAM_VEC_CLASS_NAME StreamVec1
#include "StreamVec.h"
#undef DIMENSION
#undef STREAM_VEC_CLASS_NAME
#define DIMENSION 2
#define STREAM_VEC_CLASS_NAME StreamVec2
#include "StreamVec.h"
typedef StreamVec2<2,float,cl_float2> Ivec2;
typedef StreamVec1<1,float,cl_float> Ivec1;
//#include <gtest/gtest.h>
//TYPED_TEST_CASE

int main()
{
	cl_float2 f;

	//f.s[0] = 0.0;
	f.x = 0.0;
	//flt.x =2;
	//flt.y =2;
	Ivec2 fl(f);
	Ivec1 fff(1);
	return 1;
}
#endif

