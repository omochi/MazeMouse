#include "MazeCellNode.h"
#include "MazePathSearcher.h"

MazeCellNode::MazeCellNode(MazePathSearcher &_searcher):PathNode(_searcher){
}

MazePathSearcher & MazeCellNode::mazeSearcher() const{
	return dynamic_cast<MazePathSearcher &>(searcher);
}

std::vector<PathNode *> MazeCellNode::neighbors() {
	std::vector<PathNode *>neighbors;

	Direction direction=DirectionLeft;
	for(int i=0;i<4;i++){
		if(!mazeSearcher().maze()->existsWall(pos,direction)){
			neighbors.push_back(&mazeSearcher().nodeAtPoint(pos.neighbor(direction)));
		}
		direction=DirectionRotate(direction,DirectionLeft);
	}

	return neighbors;
}

int MazeCellNode::estimatedRemainingCost() const {
	return mazeSearcher().estimatedRemainingNodeCost(*this);
}

std::string MazeCellNode::toString() const{
	char buf[256];
	snprintf(buf,sizeof(buf),"{%s,%d+%d}",
			pos.toString().c_str(),cost,estimatedRemainingCost());
	return std::string(buf);
}
