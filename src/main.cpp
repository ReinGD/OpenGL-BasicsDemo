#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "SimpleGame.h"
int main() 
{
	std::cout << "Hello OpenGL!\n";
	SimpleGame simple;
	simple.InitializeOpenGL();
	simple.run();
	simple.TerminateOpenGL();
}
#endif // !MAIN_H
