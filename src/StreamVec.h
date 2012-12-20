/*
 * StreamVec.h
 *
 *  Created on: Dec 19, 2012
 *      Author: rulk
 */

#include "StreamData.h"
namespace StingRay
{
template<class T,class IMP>
class STREAM_VEC_CLASS_NAME:public Vec<DIMENSION,T>,public StreamData
{

	mutable IMP data;
	void synchImplementationData() const
	{
#if DIMENSION == 1
		data = Vec<DIMENSION,T>::v[0];
#elif DIMENSION > 1
		data.x = Vec<DIMENSION,T>::v[0];
		data.y = Vec<DIMENSION,T>::v[1];
#endif
#if DIMENSION > 3
		data.z = Vec<DIMENSION,T>::v[2];
#endif
#if DIMENSION > 4
		data.w = Vec<DIMENSION,T>::v[3];
#endif
	}
public:


	STREAM_VEC_CLASS_NAME(const IMP & x)
	{
		setIData(&x);

	}
	STREAM_VEC_CLASS_NAME(const std::vector<std::string> & strings)
	{
#if DIMENSION == 1
		Vec<DIMENSION,T>::v[0] = (T)atof(strings[0].c_str());
#elif DIMENSION > 1
		Vec<DIMENSION,T>::v[0] =  (T)atof(strings[0].c_str());
		Vec<DIMENSION,T>::v[1] =  (T)atof(strings[1].c_str());
#endif
#if DIMENSION > 3
		Vec<DIMENSION,T>::v[2] =  (T)atof(strings[2].c_str());
#endif
#if DIMENSION > 4
		Vec<DIMENSION,T>::v[3] =  (T)atof(strings[3].c_str());
#endif

	}
	STREAM_VEC_CLASS_NAME(void * ptr)
	{
		setIData(ptr);
	}

	void * getIMemoryPtr() const
	{
		synchImplementationData();
		return (void*)&data;
	}
	size_t getISize() const
	{
		return sizeof(data);
	}
	void setIData(void * ptr)
	{
		IMP x = *((IMP*) ptr);
		data = x;
#if DIMENSION == 1
		Vec<DIMENSION,T>::v[0] = x;
#elif DIMENSION > 1
		Vec<DIMENSION,T>::v[0] = x.x;
		Vec<DIMENSION,T>::v[1] = x.y;
#endif
#if DIMENSION > 3
		Vec<DIMENSION,T>::v[2] = x.z;
#endif
#if DIMENSION > 4
		Vec<DIMENSION,T>::v[3] = x.w;
#endif
	}
	virtual ~STREAM_VEC_CLASS_NAME(){}
};
/*
StreamVec(const IMP & init)
	{
		data = init;
		v[0] = init.x;
		v[1] = init.y;
		v[2] = init.z;
		v[3] = init.w;
	}
	template < typename = typename std::enable_if< D == 3 >::type >
	StreamVec(const IMP & init)
	{
		data = init;
		v[0] = init.x;
		v[1] = init.y;
		v[2] = init.z;

	}
	template < typename = typename std::enable_if< D == 2 >::type >
	StreamVec(const IMP & init)
	{
		data = init;
		v[0] = init.x;
		v[1] = init.y;
	}
	template < typename = typename std::enable_if< D == 1 >::type >
	StreamVec(const IMP & init)
	{
		data = init;
		v[0] = init;
	}
*/
}

