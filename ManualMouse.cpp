#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <iostream>
#include <fstream>

#include "Maze.h"
#include "Mouse.h"
#include "Viewer.h"
#include "MazeCellNode.h"
#include "MazePathSearcher.h"
#include "Log.h"

std::string path;
std::ofstream dumpOfs;

Direction keyToDirection(char k){
	switch(k){
		case 'h':return DirectionLeft;
		case 'j':return DirectionBottom;
		case 'k':return DirectionTop;
		case 'l':return DirectionRight;
	}
	return DirectionLeft;
}

std::string captureWindow(){
	std::string str;
	char buf[1024];
	int w,h;
	getmaxyx(stdscr,h,w);
	for(int i=0;i<h;i++){
		mvinnstr(i,0,buf,sizeof(buf)-1);
		str.append(buf);
		str.append("\n");
	}
	return str;
}

int windowMain(){
	Viewer viewer;
	std::ifstream ifs(path.c_str());
	Maze *maze = Maze::load(ifs);
	if(maze==NULL){
		printf("load error\n");
		return EXIT_FAILURE;
	}
	Mouse mouse(*maze);

	char buf[256];
	int frameCount = 0;
	bool terminate=false;
	bool doMove=false;
	Direction moveDirection;

	//1フレーム空回し
	ungetch(' ');

	while(!terminate){
		doMove=false;

		int ch=getch();
		switch(ch){
			case ERR:
			case 'q':
				terminate=true;
				break;
			case 'h':
			case 'j':
			case 'k':
			case 'l':
				doMove=true;
				moveDirection=keyToDirection(ch);
				break;
		}

		if(doMove){
			mouse.moveWithDirection(moveDirection);
		}
		
		MazePathSearcher searcher(mouse.learnedMaze(),mouse.pos(),mouse.learnedMaze().goal(),true);
		const MazeCellNode * goal = dynamic_cast<const MazeCellNode *>(searcher.goal());	

		clear();
		move(0,0);
		printw("%s\n",viewer.printWorld(mouse.learnedMaze(),&mouse,searcher.foundCellNodePath()).c_str());

		printw("move:hjkl,quit:q\n");

//		if(searcher.found()){
//			printw("path found\n");
//			printw("%s\n",searcher.foundPathToString(searcher.foundCellNodePath()).c_str());
//		}else{
//			printw("path not found\n");
//		}
		
//		printw("log\n");
		printw("%s\n",Log::main.buf().c_str());
		Log::main.clear();

		snprintf(buf,sizeof(buf),"frame=%d\n",frameCount);

		dumpOfs << buf;
		dumpOfs << captureWindow();
		dumpOfs << "\n";		

		refresh();
	
		frameCount++;
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

	//ログ
	std::ofstream logOs("log/ManualMouseLog.txt");
	Log::main.open(logOs);

	dumpOfs.open("log/ManualMouseDump.txt");
	
	initscr();
	cbreak();
	noecho();
	
	int status=windowMain();

	endwin();

	return status;
}
