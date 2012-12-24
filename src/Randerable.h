/*
 * Randerable.h
 *
 *  Created on: Dec 22, 2012
 *      Author: rulk
 */

#ifndef RANDERABLE_H_
#define RANDERABLE_H_
#include "implementation.h"
#include "Material.h"
#include "RenderableManager.h"

namespace StingRay
{

class Renderable
{

	const Material * material;
	RenderableManager * manager;
	unsigned int id;
	friend class RenderableManager;

	void removedFromManager(RenderableManager * manager)
	{
		if(manager == this->manager)
		{
			id = NO_ID;
			this->manager = NULL;
		}
	}
	bool setManager(RenderableManager * manager,unsigned int id)
	{
		if(this->manager != NULL)
			return false;
		this->id = id;
		this->manager = manager;
		return true;
	}

public:
	static const unsigned int NO_ID = 0;
	Renderable(Material * mat):material(mat)
	{
		if(mat == NULL)
			THROW(0,"material can't be null when initializing Renderable");
		id = NO_ID;
		manager =  NULL;
	}
	/**
	 * @return id if bound to RendarableManager or Rendarable::NO_ID if not bound
	 */
	unsigned int getId()
	{
		return id;
	}
	virtual Char getType() = 0;
	const Material * getMaterial()
	{
		return material;
	}
	/**
	 * must return how much memory this object requiers
	 */
	virtual size_t getDataSize() = 0;
	/**
	 * some objects is easier to keep in separate buffers, for example vertext, index, normal buffer...
	 * so to copy the whole object we might need multiple copy operations
	 */
	virtual size_t getNumDataChunks()
	{
		return 1;
	}
	/**
	 * @parameter chunk - the number of the chunk to copy
	 * @return valid data pointer to array, or null
	 */
	virtual void* getData(size_t chunk) = 0;
	virtual size_t getDataChunkSize(size_t chunk) = 0;

	virtual ~Renderable()
	{
		if(manager != NULL)
			manager->removeRendarable(this);
	}

};

};
#endif /* RANDERABLE_H_ */
