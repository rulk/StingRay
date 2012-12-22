/*
 * MaterialKernel.cpp
 *
 *  Created on: Dec 17, 2012
 *      Author: rulk
 */

#include "MaterialKernel.h"
namespace StingRay
{

MaterialKernel::MaterialKernel(const std::string & fileName,const std::string & kernelName )
	:Kernel(fileName,kernelName)
{
	materialManager= NULL;
}
void MaterialKernel::setMaterialManager(MaterialManager * manager)
{
	if(compiled) THROW(0,"Currently you can't set Material Manager after Kernel has been compiled");
	materialManager = manager;
}
void MaterialKernel::compileKernel()
{
	if(materialManager == NULL) THROW(0,"Please set Material Manager before kernel compilation");

	std::string append = materialManager->getCompiledSource();
	programFromSource(append);
	createIKernel();
	compiled = true;
	initDefaultArgs();

	setArg(KERNEL_MATERIALSTREAM_ARG,materialManager->getCompiledStream());

}
void MaterialKernel::setCamera(Camera* cam)
{
	if(!compiled)THROW(0,"You need to compile kernel before seting camera!");
	cam->flush();
	setArg(KERNEL_CAMERA_ARG,cam->getCameraStream());
}
MaterialKernel::~MaterialKernel() {
	// TODO Auto-generated destructor stub
}
}

