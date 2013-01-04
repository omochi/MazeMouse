#pragma once

#include "PathNode.h"

#include "Cell.h"
#include "Point.h"

class MazePathSearcher;

class MazeCellNode : public PathNode{
	public:
		Point pos;
		
		MazeCellNode(MazePathSearcher &_searcher);

		MazePathSearcher &mazeSearcher() const;
		virtual std::vector<PathNode *> neighbors();
		virtual int estimatedRemainingCost() const;

		virtual std::string toString() const;
};

class MazeCellNodePosEquals{
	public:
		const Point &pos;
		MazeCellNodePosEquals(const Point &_pos):pos(_pos){}
		bool operator()(const MazeCellNode *node)const{
			return pos.equals(node->pos);
		}
};
