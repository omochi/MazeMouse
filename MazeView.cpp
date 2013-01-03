#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "Maze.h"
#include "Viewer.h"

int main(int argc,char *argv[]){
	char *arg0=argv[0];
	//特にオプション無いね
	char ch;
	bool optError=false;
	while ((ch = getopt(argc, argv, "")) != -1) {
		switch (ch) {
			case '?':
				optError=true;
				break;
		}
	}
	argc -= optind;
	argv += optind;	

	if(argc<2 || optError){
		printf("usage: %s file1 file2...\n",arg0);
		return EXIT_FAILURE;
	}

	Viewer viewer;

	for(int i=1;i<argc;i++){
		char *path=argv[i];
		printf("file:%s\n",path);
		std::ifstream ifs(path);
		Maze *maze=Maze::load(ifs);
		if(maze==NULL){
			printf("load error\n");
			continue;
		}
		
		printf("%s\n",viewer.printWorld(*maze,NULL).c_str());

		delete maze;
	}

	return EXIT_SUCCESS;	
}
