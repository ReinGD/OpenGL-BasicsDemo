/*====================
	MADE BY REINGD
====================*/


#ifndef MAIN_H
#define MAIN_H

#include "SimpleGame.h"
int main() 
{
	GDWriter::write("Staring OpenGL\n");

	SimpleGame simple;
	simple.InitializeOpenGL();
	simple.run();
	simple.TerminateOpenGL();

	GDWriter::write("Exiting OpenGL\n");
}
#endif // !MAIN_H
