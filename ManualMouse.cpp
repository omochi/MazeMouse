#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "Maze.h"
#include "Mouse.h"
#include "Viewer.h"

int main(int argc,char *argv[]){
	char *arg0=argv[0];
	char ch;
	bool optError=false;
	while((ch=getopt(argc,argv,""))!=-1){
		switch(ch){
			case '?':
				optError=true;
				break;
		}
	}
	argc -= optind;
	argv += optind;

	if(argc < 2 || optError){
		printf("usage: %s file\n",arg0);
		return EXIT_FAILURE;
	}

	Viewer viewer;
	Maze *maze = Maze::load(std::ifstream(argv[1]));
	if(maze==NULL){
		printf("load error\n");
		return EXIT_FAILURE;
	}
	Mouse mouse(*maze);

	printf("%s\n",viewer.printWorld(*maze,&mouse));

	delete maze;
}
