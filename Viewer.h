#pragma once
#include <stdio.h>
#include <string>
#include "Maze.h"
#include "Mouse.h"
class Viewer{
	public:
		std::string printWorld(const Maze &maze,const Mouse *mouse) const;

};
