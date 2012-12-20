/*
 * SphereTracerKernel.cpp
 *
 *  Created on: Dec 9, 2012
 *      Author: rulk
 */

#include "SphereTracerKernel.h"

namespace StingRay {

SphereTracerKernel::SphereTracerKernel()
	:MaterialKernel("//home/rulk/src/raytracer-wsp/StingRay/cl/sphere_tracer.cl","sphtracer") {
	// TODO Auto-generated constructor stub
	Image img = Core::getInstance()->getRenderingImage();
	setArg(0,&img);
}
void SphereTracerKernel::setSphereStream(const SphereStream * speres)
{
	setArg(3,speres->getPositionStream());
	setArg(4,speres->getRadiusColorStream());
}
SphereTracerKernel::~SphereTracerKernel() {
	// TODO Auto-generated destructor stub
}

} /* namespace SimpleRayTracer */
