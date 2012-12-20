/*
 * MaterialKernel.h
 *
 *  Created on: Dec 17, 2012
 *      Author: rulk
 */

#ifndef MATERIALKERNEL_H_
#define MATERIALKERNEL_H_
#include "implementation.h"
#include "MaterialManager.h"
#include "Camera.h"
namespace StingRay
{
#define KERNEL_MATERIALSTREAM_ARG 2
class MaterialKernel:public Kernel {
	MaterialManager * materialManager;
public:
	MaterialKernel(const std::string & fileName,const std::string & kernelName = "renderKernel");
	void setMaterialManager(MaterialManager * manager);
	void setCamera(Camera* cam);
	virtual void compileKernel();
	virtual ~MaterialKernel();
};
}
#endif /* MATERIALKERNEL_H_ */
