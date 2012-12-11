/*
 * SphereTracerKernel.cpp
 *
 *  Created on: Dec 9, 2012
 *      Author: rulk
 */

#include "SphereTracerKernel.h"

namespace SimpleRayTracer {

SphereTracerKernel::SphereTracerKernel()
	:Kernel("sphere_tracer.cl","main") {
	// TODO Auto-generated constructor stub
	Image img = Core::getInstance()->getRenderingImage();
	setArg(0,&img);
}
void SphereTracerKernel::setCamera(const Camera * cam )
{
	setArg(1,cam->getCameraStream());
}
void SphereTracerKernel::setSphereStream(const SphereStream * speres)
{
	setArg(2,speres->getPositionStream());
	setArg(3,speres->getRadiusColorStream());
}
SphereTracerKernel::~SphereTracerKernel() {
	// TODO Auto-generated destructor stub
}

} /* namespace SimpleRayTracer */