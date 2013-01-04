#include "MazePathSearcher.h"
#include "MazeCellNode.h"
#include "Log.h"
MazePathSearcher::MazePathSearcher(const Maze &maze,const Point &start,const Point &goal):
	m_maze(maze){
	searchShortestPath(nodeAtPoint(start),nodeAtPoint(goal));
}
MazePathSearcher::~MazePathSearcher(){
	for(std::map<Point,MazeCellNode *>::iterator it=m_nodes.begin();it!=m_nodes.end();it++){
		delete (*it).second;
	}
}

const Maze & MazePathSearcher::maze() const{
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
