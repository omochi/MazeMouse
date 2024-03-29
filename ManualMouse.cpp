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
bool autoDriven;

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
	MazePathSearcher searcher;
	searcher.m_estimateEnabled = true;

	char buf[256];
	int frameCount = 0;
	bool terminate=false;
	bool doMove=false;
	Direction moveDirection;

	//1フレーム空回し
	ungetch(' ');

	while(!terminate){
		doMove=false;

		if(autoDriven){
			//自動走行
			std::vector<MazeCellNode *> path = searcher.foundCellNodePath();
			if(mouse.pos().equals(maze->goal())){
				Log::main.add("auto drive finished\n");
				terminate = true;	
			}else if(path.size()>=2){
				doMove=true;
				moveDirection=path[0]->pos.directionTo(path[1]->pos);
			}else{
				if(frameCount>0){
					//0フレーム目だけは空打ち
					Log::main.add("auto drive path not found\n");
					terminate = true;
				}
			}
		}else{
			//手動走行
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
		}

		if(doMove){
			mouse.moveWithDirection(moveDirection);
		}
	
		searcher.release();	
		searcher.searchShortestPath(&mouse.learnedMaze(),mouse.pos(),mouse.learnedMaze().goal());

		
		//画面描画
		clear();
		move(0,0);
		printw("%s\n",viewer.printWorld(mouse.learnedMaze(),&mouse,searcher.foundCellNodePath()).c_str());

		if(!autoDriven){
			printw("move:hjkl,quit:q\n");
		}

		printw("%s\n",Log::main.buf().c_str());
		Log::main.clear();
		
		//画面の保存
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
	autoDriven=false;
	while((ch=getopt(argc,argv,"a"))!=-1){
		switch(ch){
			case '?':
				optError=true;
				break;
			case 'a':
				autoDriven=true;
				break;
		}
	}
	argc -= optind-1;
	argv += optind-1;


	if(argc < 2 || optError){
		printf("usage : %s [-a] file\n",arg0);
		printf("   -a : auto driven\n");
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
