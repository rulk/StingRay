//============================================================================
// Name        : simpleRayTracer.cpp
// Author      : Leonid Sinyakov
// Version     :
// Copyright   : This source is copyrighed by Leonid Sinyakov, All Rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================
#ifndef UNIT_TESTS
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <GL/glxew.h>
#include <GL/glut.h>
#include "implementation.h"
#include "Sphere.h"
#include "MaterialKernel.h"
using namespace std;
using namespace StingRay;
void display();
int main(int argc, char **argv) {

	glutInit(&argc,argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(256,256);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE );
	glutCreateWindow("StingRay");
	//glutDisplayFunc(display);
	glutReshapeWindow(256,256);
	glewInit();
	//glutMainLoop();
	display();
	sleep(5000);
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

    MaterialManager * materials = new MaterialManager("/home/rulk/src/raytracer-wsp/StingRay/src/material/"
    		,"/home/rulk/src/raytracer-wsp/StingRay/src/material/");
    materials->loadFile("basic.material");

    materials->compile();
    Material * mat = materials->getMaterial("simpleColor");
    Material * mat1 = materials->getMaterial("complexColor");
    std::cout<<mat<<std::endl;


    RenderableManager * renderables = new RenderableManager();

    Sphere * sphere = new Sphere(mat,Fvec4(2,0,-8,1),1);
    Sphere * sphere1 = new Sphere(mat1,Fvec4(-2,0,-8,1),1);
    Sphere * sphere2 = new Sphere(mat1,Fvec4(0,2,-8,1),1);
    /*SphereStream * spheres = new SphereStream(1,STREAM_READ);
    spheres->put(Vector4I(2,0,-8,1),1,Vector3I(0,0,1));
    spheres->flush();
     */
    renderables->registerRendarable(sphere);
    renderables->registerRendarable(sphere1);
    renderables->registerRendarable(sphere2);
    MaterialKernel * kernel = new MaterialKernel("/home/rulk/src/raytracer-wsp/StingRay/cl/sphere_tracer.cl");
    kernel->setMaterialManager(materials);
    kernel->setRenderableManager(renderables);
    kernel->compileKernel();

    kernel->setCamera(cam);


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
#endif
