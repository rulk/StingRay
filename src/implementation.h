/*
 * implementation.h
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef IMPLEMENTATION_H_
#define IMPLEMENTATION_H_

enum SteramType
{
	//!Readable stream by rendering calls to underling engine, Sting Ray can only write this stream
	STREAM_READ,
	//!Writable stream by rendering calls to underling engine, Sting Ray can only read this stream
	STREAM_WRITE,
	STREAM_READ_WRITE
};
#include "OpenClImpl.h"
#endif /* IMPLEMENTATION_H_ */
