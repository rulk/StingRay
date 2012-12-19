/*
 * StreamVec.h
 *
 *  Created on: Dec 19, 2012
 *      Author: rulk
 */

//#ifndef STREAMVEC_H_
//#define STREAMVEC_H_
#include <type_traits>
template<int D,class T,class IMP>
class StreamVecDIMENSION:public Vec<D,T>,public StreamData<IMP>
{
protected:


public:


	StreamVecDIMENSION(const IMP & x)
	{
		StreamData<IMP>::data = x;
#if DIMENSION == 1
		Vec<D,T>::v[0] = x;
#elif DIMENSION > 1
		Vec<D,T>::v[0] = x.x;
		Vec<D,T>::v[1] = x.y;
#endif
#if DIMENSION > 3
		Vec<D,T>::v[2] = x.z;
#endif
#if DIMENSION > 4
		Vec<D,T>::v[3] = x.w;
#endif

	}

	/*StreamData & operator = (const IMP & init)
	{
		return *this;
	}*/
	StreamVecDIMENSION(const std::vector<std::string> & strings)
	{

	}
	StreamVecDIMENSION(void * ptr)
	{

	}
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
//#endif /* STREAMVEC_H_ */
