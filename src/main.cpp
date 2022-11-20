#ifndef MAIN_H
#define MAIN_H

#include "SimpleGame.h"
#include <iostream>
int main() 
{
	std::cout << "Hello OpenGL!\n";
	SimpleGame simple;
	simple.InitializeOpenGL();
	simple.run();
	simple.TerminateOpenGL();
}
#endif // !MAIN_H
