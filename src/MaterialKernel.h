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
#include "RenderableManager.h"
namespace StingRay
{
class MaterialKernel:public Kernel {
	MaterialManager * materialManager;
	RenderableManager * renderableManager;
public:
	static const size_t MATERIAL_STREAM_ARG = 2;
	static const size_t RENDERABLE_INDEX_STREAM_ARG = 3;
	static const size_t RENDERABLE_DATA_STREAM_ARG = 4;

	MaterialKernel(const std::string & fileName,const std::string & kernelName = "renderKernel");
	void setMaterialManager(MaterialManager * manager);
	void setRenderableManager(RenderableManager * manager);
	void setCamera(Camera* cam);
	virtual void compileKernel();
	virtual ~MaterialKernel();
};
}
#endif /* MATERIALKERNEL_H_ */
