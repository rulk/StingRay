/*
 * Exception
 *
 *  Created on: Dec 8, 2012
 *      Author: rulk
 */

#ifndef EXCEPTION_
#define EXCEPTION_

#include <string>
#include <iostream>
namespace StingRay
{
class Exception
{
	int err,line;
	std::string message,file;
public:
	Exception(int err,std::string message,std::string file,int line):
	message(message),file(file)
	{
		this->err = err;
		this->line = line;
		std::cout<<"Error "<<err<<" has occured:"<<message<<" in file:"<<file<<" line:"<<line<<std::endl;
	}
};
#define THROW(num,msg) throw Exception(num,msg,__FILE__,__LINE__)
}



#endif /* EXCEPTION_ */
