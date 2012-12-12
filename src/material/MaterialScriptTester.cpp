//============================================================================
// Name        : MaterialScriptTester.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "MaterialProgramManager.h"
#include "ConfigLoader.h"
using namespace std;
using namespace StingRay;
int main() {

	MaterialProgramManager * manager = new MaterialProgramManager("/home/rulkw/src/c++tests/MaterialScriptTester/src/");
	const MaterialProgramm & program = manager->getProgram("script_example");
	cout<<program.getParamId("color")<<" indx:"<<program.getParamOffset("index")<<std::endl;
	manager->getProgram("phong");
	cout << manager->buildSource() << endl; // prints !!!Hello World!!!

	StingRay::ConfigLoader * loader = new StingRay::ConfigLoader(".material");
	std::ifstream in("/home/rulkw/src/c++tests/MaterialScriptTester/src/basic.material", std::ios::binary);
	loader->parseScript(in);

	StingRay::ConfigNode * node = loader->getConfigScript("material basic/phong");

	if(node != NULL)
		cout<<node->findChild("ambient")->getValue()<<std::endl;

	std::map <std::string, StingRay::ConfigNode*> m = loader->getAllConfigScripts();
	std::map <std::string, StingRay::ConfigNode*>::iterator it =m.begin();
	cout<<it->first<<std::endl;
	return 0;
}
