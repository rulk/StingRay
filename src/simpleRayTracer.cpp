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
    Camera * cam = new Camera();

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

	Core::getInstance()->dumpImage("out.png");
	Core::getInstance()->flushQue();
	Core::getInstance()->finishQue();
	delete kernel;

	Core::destroy();
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
