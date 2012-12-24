/*
 * RenderableManager.cpp
 *
 *  Created on: Dec 22, 2012
 *      Author: rulk
 */

#include "RenderableManager.h"
#include "VoidStream.h"
#include "Randerable.h"
namespace StingRay
{

RenderableManager::RenderableManager()
{
	// TODO Auto-generated constructor stub
	indexStream = NULL;
	dataStream = NULL;
	idCounter = 0;
	streamsReady = false;
}

RenderableManager::~RenderableManager()
{
	// TODO Auto-generated destructor stub
}
bool RenderableManager::registerRendarable(Renderable * renderable)
{
	idCounter++;
	if(!renderable->setManager(this,idCounter))
	{
		idCounter--;
		return false;
	}
	renderables[idCounter] = renderable;
	return true;
}
void RenderableManager::removeRendarable(Renderable * renderable)
{
	if(Renderable::NO_ID == renderable->getId())
		return;
	renderables.erase(renderable->getId());
	renderable->removedFromManager(this);
}
void RenderableManager::rebuildAllStreams()
{
	renderableInfol.clear();
	idToNumber.clear();
	size_t number =0,offsetData = 0,offsetIndex = 0;
	std::map<unsigned int,Renderable*>::iterator it = renderables.begin();
	for(;it != renderables.end();it++)
	{
		RenderableSeuenceInfo info;
		info.id = it->second->getId();
		info.deleted = false;
		info.dataOffset = offsetData;
		info.indexOffset = offsetIndex;
		info.number = number;

		renderableInfol[info.number] = info;
		idToNumber[info.id] = info.number;
		offsetData += it->second->getDataSize();
		number++;
	}
	if(indexStream != NULL)
		delete indexStream;
	if(dataStream != NULL)
			delete dataStream;
	indexStream = new VoidStream(sizeof(uInt)+number*(sizeof(uInt)+sizeof(uInt)+sizeof(uInt)+sizeof(uInt)),STREAM_READ);
	dataStream = new VoidStream(offsetData,STREAM_READ);
	indexStream->putData<uInt>(number);
	for(size_t i=0;i<number;i++)
	{
		RenderableSeuenceInfo info =renderableInfol[i];
		Renderable * r = renderables[info.id];
		indexStream->putData<uInt>(r->getType());
		indexStream->putData<uInt>(info.dataOffset);
		indexStream->putData<uInt>(r->getMaterial()->getProgramId());
		indexStream->putData<uInt>(r->getMaterial()->getMaterialDataOffset());


		for(size_t c = 0;c<r->getNumDataChunks();c++)
		{
			dataStream->putData(r->getData(c),r->getDataChunkSize(c));
		}
	}
	indexStream->flushData();
	dataStream->flushData();
	streamsReady = true;
}
} /* namespace StingRay */
