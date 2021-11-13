#include<iostream>

#include "myConfig.h"

int fun()
{
	
	return 1;
}


int main()
{
	std::cout<<"Hello Cmake World"<<std::endl;
	std::cout<<myDef<<std::endl;
	//std::cout<<Tutorial_VERSION_MAJOR << "."<< Tutorial_VERSION_MINOR <<<<std::endl;
	
	std::cout<<fun()<<std::endl;
	
}