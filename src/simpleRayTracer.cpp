//============================================================================
// Name        : simpleRayTracer.cpp
// Author      : Leonid Sinyakov
// Version     :
// Copyright   : This source is copyrighed by Leonid Sinyakov, All Rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "implementation.h"
#include "SphereTracerKernel.h"
using namespace std;
using namespace StingRay;

int main() {


	Core::init(640,640);
	Core::getInstance()->initImageRendering();
	void * data = malloc(sizeof(int)*20);
	int i  = 11;
	int & b = i;
	*((int*)(data+sizeof(int))) = b;

	std::cout<<*((int*)(data+sizeof(int)))<<std::endl;
	return 0;
    /*Camera * cam = new Camera();

    cam->setPosition(Vector4I(0,0,0,1));
    cam->setDirection(Vector4I(0,0,-1,0),Vector4I(0,1,0,0));
    cam->setFovDeg(30,30);
    cam->flush();

    SphereStream * spheres = new SphereStream(1,STREAM_WRITE);
    spheres->put(Vector4I(2,0,-8,1),1,Vector3I(1,1,0));
    spheres->flush();

    SphereTracerKernel * kernel = new SphereTracerKernel();
    kernel->setCamera(cam);
    kernel->setSphereStream(spheres);

	size_t global_item_size = 640*640; // Process the entire lists
    size_t local_item_size = 640;

	kernel->run(Core::getInstance()->getQue(),&global_item_size,&local_item_size);

	//streamC.sync();

	Core::getInstance()->dumpImage("out.png");*/
	Vector4ImplStream *streama = new Vector4ImplStream(60,STREAM_WRITE);
	Vector4ImplStream *streamb = new Vector4ImplStream(60,STREAM_WRITE);
	for(int i=0;i<60;i++)
	{
		streama->put(Vector4I(0.1,0.0,0.1,0.1));
		streamb->put(Vector4I(0.1,0.0,0.1,0.1));
	}
	streama->flush();
	streamb->flush();
	Vector4ImplStream *streamc = new Vector4ImplStream(60,STREAM_READ);
	Kernel * k = new Kernel("/home/rulkw/src/c++tests/StingRay/cl/add.cl","vector_add" );
	k->setArg(0,streama);
	k->setArg(1,streamb);
	k->setArg(2,streamc);
	size_t global_item_size = 60; // Process the entire lists
	size_t local_item_size = 60;

	k->run(Core::getInstance()->getQue(),&global_item_size,&local_item_size);
	streamc->sync();
	for(int i=0;i<60;i++)
	{
		Vector4Impl vec;
		streamc->get(i,vec);
		std::cout<<vec.x<<std::endl;
	}
	Core::getInstance()->flushQue();
	Core::getInstance()->finishQue();
	delete k;

	Core::destroy();
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
