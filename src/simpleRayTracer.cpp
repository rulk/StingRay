//============================================================================
// Name        : simpleRayTracer.cpp
// Author      : Leonid Sinyakov
// Version     :
// Copyright   : This source is copyrighed by Leonid Sinyakov, All Rights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================
#ifndef UNIT_TESTS
#include <iostream>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <GL/glxew.h>
#include <GL/glut.h>
#include "TriMesh.h"
#include "implementation.h"
#include "Sphere.h"
#include "MaterialKernel.h"
#include "ManualMesh.h"
using namespace std;
using namespace StingRay;
void display();
void * kill_all_thread(void * ptr)
{
	//std::cout<<"Killing therad started"<<std::endl;
	//std::cout.flush();
	unsigned int i = 25;
	while(i > 0)
	{

		i = sleep(i);
		std::cout<<"slept for:"<<i<<std::endl;
	}
	std::cout<<"Time is up harakiri! :"<<i<<std::endl;
	//kill(0,SIGABRT);
	return NULL;
}
int main(int argc, char **argv) {

	pthread_t thread1;
	pthread_create(&thread1,NULL,kill_all_thread,NULL);
	glutInit(&argc,argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512,512);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE );
	glutCreateWindow("StingRay");
	//glutDisplayFunc(display);
	glutReshapeWindow(512,512);
	glewInit();
	//glutMainLoop();
	display();
	sleep(5000);
	return 1;
}
void display()
{

	Core::init(512,512);
	Core::getInstance()->initImageRendering();


    Camera * cam = new Camera();

    cam->setPosition(Vector4I(0,-8,-8,1));
    cam->setDirection(Vector4I(0,-1,-1,0),Vector4I(0,1,0,0));
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
    ManualMesh manual;





    TriMesh *themesh = TriMesh::read("/home/rulk/src/raytracer-wsp/StingRay/cube.obj");
    if (!themesh)
    			THROW(0,"No such mesh...");
    themesh->need_normals();
    themesh->need_tstrips();
    themesh->need_bsphere();
    int offset = 0,len = 0,pIndex;
    manual.begin(mat);
    for(int i=0;i<themesh->tstrips.size();i++)
    {
    	if( i >= offset+len)
    	{
    		offset = i+1;
    		len = themesh->tstrips[i];
    		manual.beginStrip();
    		continue;
    	}
    	pIndex = themesh->tstrips[i];
    	manual.position(themesh->vertices[pIndex][0],themesh->vertices[pIndex][1],themesh->vertices[pIndex][2]);
    }
    manual.normal(Fvec4(0,1,0,0));
    std::cout<<"Size:"<<themesh->tstrips.size()<<std::endl;
    TriangelMesh * mesh = manual.getTriangelMesh();

    /*SphereStream * spheres = new SphereStream(1,STREAM_READ);
    spheres->put(Vector4I(2,0,-8,1),1,Vector3I(0,0,1));
    spheres->flush();
     */
   // renderables->registerRendarable(sphere);
   // renderables->registerRendarable(sphere1);
   // renderables->registerRendarable(sphere2);
    renderables->registerRendarable(mesh);
    MaterialKernel * kernel = new MaterialKernel("/home/rulk/src/raytracer-wsp/StingRay/cl/sphere_tracer.cl");
    kernel->setMaterialManager(materials);
    kernel->setRenderableManager(renderables);
    kernel->compileKernel();

    kernel->setCamera(cam);


	size_t global_item_size = 512*512; // Process the entire lists
    size_t local_item_size = 512;

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
