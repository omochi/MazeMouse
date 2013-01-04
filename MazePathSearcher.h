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
		const Maze *m_maze;
		std::map<Point,MazeCellNode *> m_nodes;		
	public:
		bool m_estimateEnabled;
		
		MazePathSearcher();
		virtual ~MazePathSearcher();
		virtual void release();

		const Maze * maze() const;
		MazeCellNode & nodeAtPoint(const Point &pos);
		virtual void searchShortestPath(const Maze *maze,const Point &start,const Point &goal);
		std::vector<MazeCellNode *> foundCellNodePath() const;
		std::string foundPathToString(std::vector<MazeCellNode *>path);

		int estimatedRemainingNodeCost(const MazeCellNode &node)const;
};
