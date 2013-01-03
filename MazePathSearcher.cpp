#include "MazePathSearcher.h"
#include "MazeCellNode.h"
MazePathSearcher::MazePathSearcher(const Maze &maze,const Point &start,const Point &goal):
	m_maze(maze){
	searchShortestPath(nodeAtPoint(start),nodeAtPoint(goal));
}
MazePathSearcher::~MazePathSearcher(){
	for(std::map<Point,MazeCellNode *>::iterator it=m_nodes.begin();it!=m_nodes.end();it++){
		delete (*it).second;
	}
}


MazeCellNode & MazePathSearcher::nodeAtPoint(const Point &pos){
	if(m_nodes.find(pos)==m_nodes.end()){
		MazeCellNode *cellNode = new MazeCellNode();
		cellNode->pos = pos;
		m_nodes.insert(std::pair<Point,MazeCellNode *>(pos,cellNode));	
	}
	return *m_nodes[pos];
}	

std::vector<PathNode *> MazePathSearcher::nodeNeighbors(const PathNode &node){
	const MazeCellNode &cellNode = dynamic_cast<const MazeCellNode &>(node);
	
	std::vector<PathNode *>neighbors;

	Direction directions[] = {DirectionLeft,DirectionTop,DirectionRight,DirectionBottom};
	for(int i=0;i<4;i++){
		Direction direction = directions[i];
		if(!m_maze.existsWall(cellNode.pos,direction)){
			neighbors.push_back(&nodeAtPoint(cellNode.pos.neighbor(direction)));
		}
	}
	
	return neighbors;
}

int MazePathSearcher::nodeEstimatedRemainingCost(const PathNode &node){
	return 0;
}

std::vector<MazeCellNode *> MazePathSearcher::foundCellNodePath() const{
	std::vector<MazeCellNode *> nodes;
	std::vector<PathNode *>path = foundPath();
	for(std::vector<PathNode *>::iterator it = path.begin();it!=path.end();it++){
		nodes.push_back(dynamic_cast<MazeCellNode *>(*it));
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
		snprintf(buf,sizeof(buf),"{%s,%d+%d}",
				(*it)->pos.toString().c_str(),
				(*it)->cost,
				nodeEstimatedRemainingCost(*dynamic_cast<PathNode *>(*it)));
		str.append(buf);
	}
	return str;
}
