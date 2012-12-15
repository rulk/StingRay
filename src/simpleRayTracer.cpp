//============================================================================
// Name        : simpleRayTracer.cpp
// Author      : Leonid Sinyakov
// Version     :
// Copyright   : This source is copyrighed by Leonid Sinyakov, All Rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <GL/glxew.h>
#include <GL/glut.h>
#include "implementation.h"
#include "SphereTracerKernel.h"
using namespace std;
using namespace StingRay;
void display();
int main(int argc, char **argv) {

	/*glutInit(&argc,argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(256,256);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE );
	glutCreateWindow("StingRay");
	glutDisplayFunc(display);
	glutReshapeWindow(256,256);
	glewInit();
	glXGetCurrentDisplay();
	glutMainLoop();*/
	display();
	return 1;
}
void display()
{

	Core::init(256,256);
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

	size_t global_item_size = 256*256; // Process the entire lists
    size_t local_item_size = 256;

	kernel->run(Core::getInstance()->getQue(),&global_item_size,&local_item_size);

	//streamC.sync();

	Core::getInstance()->dumpImage("out.png");
	Core::getInstance()->flushQue();
	Core::getInstance()->finishQue();
	delete kernel;

	Core::destroy();
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return ;

}
