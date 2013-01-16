/*
 * FrameListner.h
 *
 *  Created on: Jan 7, 2013
 *      Author: rulk
 */

#ifndef FRAMELISTNER_H_
#define FRAMELISTNER_H_

class FrameListner
{
public:
	virtual bool frameStart(float sinceLastTime){return true;}
	virtual bool frameQueued(float sinceLastTime){return true;}
	virtual ~FrameListner(){};
};


#endif /* FRAMELISTNER_H_ */
