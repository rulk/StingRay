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
#include "MaterialKernel.h"
namespace StingRay {

class SphereTracerKernel:public MaterialKernel {
public:
	SphereTracerKernel();

	void setSphereStream(const SphereStream * speres);

	virtual ~SphereTracerKernel();
};

} /* namespace SimpleRayTracer */
#endif /* SPHERETRACERKERNEL_H_ */
