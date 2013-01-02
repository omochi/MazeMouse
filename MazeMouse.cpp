#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Maze.h"

int main(int argc,char *argv[]){
	
	Maze *maze=Maze::load(std::cin);
	if(maze==NULL)return EXIT_FAILURE;
	
	printf("%s\n",maze->toString().c_str());

	delete maze;
	maze=NULL;

	return EXIT_SUCCESS;	
}
