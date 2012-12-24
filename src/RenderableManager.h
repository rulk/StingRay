/*
 * RenderableManager.h
 *
 *  Created on: Dec 22, 2012
 *      Author: rulk
 */

#ifndef RENDERABLEMANAGER_H_
#define RENDERABLEMANAGER_H_
#include <map>
#include "implementation.h"
namespace StingRay
{
class Renderable;
struct RenderableSeuenceInfo
{
	unsigned int id;
	size_t number;
	size_t indexOffset;
	size_t dataOffset;
	bool deleted;
};
class RenderableManager
{
	VoidStream * indexStream;
	VoidStream * dataStream;
	std::map<unsigned int,Renderable*> renderables;
	std::map<size_t, RenderableSeuenceInfo> renderableInfol;
	std::map<size_t,unsigned int> idToNumber;
	unsigned int idCounter;
	bool streamsReady;
	void rebuildAllStreams();

public:
	RenderableManager();
	const VoidStream * getDataStream()
	{
		if(!streamsReady)rebuildAllStreams();
		return dataStream;
	}
	const VoidStream * getIndexStream()
	{
		if(!streamsReady)rebuildAllStreams();
		return indexStream;
	}
	bool registerRendarable(Renderable * renderable);
	void removeRendarable(Renderable * renderable);
	virtual ~RenderableManager();
};

} /* namespace StingRay */
#endif /* RENDERABLEMANAGER_H_ */
