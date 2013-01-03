#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <iostream>
#include <fstream>

#include "Maze.h"
#include "Mouse.h"
#include "Viewer.h"

std::string path;

int windowMain(){
	Viewer viewer;
	std::ifstream ifs(path.c_str());
	Maze *maze = Maze::load(ifs);
	if(maze==NULL){
		printf("load error\n");
		return EXIT_FAILURE;
	}
	Mouse mouse(*maze);

	bool firstFrame=true;
	bool terminate=false;
	bool doMove=false;
	Direction moveDirection;

	while(!terminate){
		doMove=false;

		if(firstFrame){
			firstFrame=false;
		}else{
			int ch=getch();
			switch(ch){
				case ERR:
				case 'q':
					terminate=true;
					break;
				case 'h':
					doMove=true;
					moveDirection=DirectionLeft;
					break;
				case 'j':
					doMove=true;
					moveDirection=DirectionBottom;
					break;
				case 'k':
					doMove=true;
					moveDirection=DirectionTop;
					break;
				case 'l':
					doMove=true;
					moveDirection=DirectionRight;
					break;
			}
		}

		if(doMove){
			if(mouse.direction()==moveDirection){
				mouse.goStraight();
			}else if(DirectionRotate(mouse.direction(),DirectionLeft)==moveDirection){
				mouse.turnLeft();
			}else if(DirectionRotate(mouse.direction(),DirectionRight)==moveDirection){
				mouse.turnRight();
			}else{
				mouse.turnLeft();
			}

		}
		firstFrame=false;
			
		move(0,0);
		printw("%s\n",viewer.printWorld(mouse.learnedMaze(),&mouse).c_str());

		printw("move:hjkl,quit:q\n");

		refresh();
	}

	delete maze;

	return EXIT_SUCCESS;
}

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
	argc -= optind-1;
	argv += optind-1;


	if(argc < 2 || optError){
		printf("usage: %s file\n",arg0);
		return EXIT_FAILURE;
	}

	path=std::string(argv[1]);

	initscr();
	cbreak();
	noecho();
	
	int status=windowMain();

	endwin();

	return status;
}
