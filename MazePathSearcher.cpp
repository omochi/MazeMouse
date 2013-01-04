#include "MazePathSearcher.h"

#include <stdlib.h>
#include "MazeCellNode.h"
#include "Log.h"
MazePathSearcher::MazePathSearcher():
	m_maze(NULL),m_estimateEnabled(false){
}
MazePathSearcher::~MazePathSearcher(){
}

void MazePathSearcher::release(){
	m_maze=NULL;
	for(std::map<Point,MazeCellNode *>::iterator it=m_nodes.begin();it!=m_nodes.end();it++){
		delete (*it).second;
	}
	m_nodes.clear();
	PathSearcher::release();
}

const Maze * MazePathSearcher::maze() const{
	return m_maze;
}

MazeCellNode & MazePathSearcher::nodeAtPoint(const Point &pos) {
	if(m_nodes.find(pos)==m_nodes.end()){
		MazeCellNode *cellNode = new MazeCellNode(*this);
		cellNode->pos = pos;
		m_nodes.insert(std::pair<Point,MazeCellNode *>(pos,cellNode));	
	}
	return *m_nodes[pos];
}

void MazePathSearcher::searchShortestPath(const Maze *maze,const Point &start,const Point &goal){
	release();
	m_maze = maze;
	PathSearcher::searchShortestPath(nodeAtPoint(start),nodeAtPoint(goal));
}

std::vector<MazeCellNode *> MazePathSearcher::foundCellNodePath() const{
	std::vector<MazeCellNode *> nodes;
	std::vector<PathNode *>path = foundPath();
	for(std::vector<PathNode *>::iterator it = path.begin();it!=path.end();it++){
		MazeCellNode *node = dynamic_cast<MazeCellNode *>(*it);
		nodes.push_back(node);
	}
	return nodes;
}

std::string MazePathSearcher::foundPathToString(std::vector<MazeCellNode *>path){
	char buf[256];
	std::string str;
	for(std::vector<MazeCellNode *>::iterator it = path.begin();it!=path.end();it++){			
		if(it!=path.begin()){
			str.append("->");
		}
		str.append((*it)->toString());
	}
	return str;
}


int MazePathSearcher::estimatedRemainingNodeCost(const MazeCellNode &node)const{
	if(m_estimateEnabled){
		MazeCellNode *cellGoal = dynamic_cast<MazeCellNode *>(goal());
		return abs(cellGoal->pos.x-node.pos.x)+abs(cellGoal->pos.y-node.pos.y);
	}else{
		return 0;
	}	
}


