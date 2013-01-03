#pragma once

#include "PathNode.h"

#include "Cell.h"
#include "Point.h"

class MazeCellNode : public PathNode{
	public:
		Point pos;
};

class MazeCellNodePosPred{
	public:
		const Point &pos;
		MazeCellNodePosPred(const Point &_pos):pos(_pos){}
		bool operator()(const MazeCellNode *node)const{
			return pos.equals(node->pos);
		}
};
