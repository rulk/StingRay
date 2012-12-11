/*
 * SphereTracerKernel.h
 *
 *  Created on: Dec 9, 2012
 *      Author: rulk
 */

#ifndef SPHERETRACERKERNEL_H_
#define SPHERETRACERKERNEL_H_
#include "implementation.h"
#include "Camera.h"
#include "SphereStream.h"
namespace SimpleRayTracer {

class SphereTracerKernel:public Kernel {
public:
	SphereTracerKernel();

	void setCamera(const Camera * cam );
	void setSphereStream(const SphereStream * speres);

	virtual ~SphereTracerKernel();
};

} /* namespace SimpleRayTracer */
#endif /* SPHERETRACERKERNEL_H_ */
