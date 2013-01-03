#pragma once

#include <vector>
#include <string>
#include <map>

#include "PathSearcher.h"
#include "Maze.h"
#include "Cell.h"

class MazeCellNode;

class MazePathSearcher : public PathSearcher{
	private:
		const Maze &m_maze;
		std::map<Point,MazeCellNode *> m_nodes;		
	public:
		MazePathSearcher(const Maze &maze,const Point &start,const Point &goal);
		virtual ~MazePathSearcher();
	
		MazeCellNode & nodeAtPoint(const Point &pos);
		virtual std::vector<PathNode *> nodeNeighbors(const PathNode &node);
		virtual int nodeEstimatedRemainingCost(const PathNode &node);
	
		std::vector<MazeCellNode *> foundCellNodePath() const;

		std::string foundPathToString(std::vector<MazeCellNode *>path);


};
