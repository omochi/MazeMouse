#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "Maze.h"
#include "Mouse.h"
#include "MazeCellNode.h"
#include "MazePathSearcher.h"
class Viewer{
	public:
		std::string printWorld(const Maze &maze,const Mouse *mouse) const;
		std::string printWorld(const Maze &maze,const Mouse *mouse,std::vector<MazeCellNode *>path) const;
};
