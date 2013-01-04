#include "PathSearcher.h"
#include <algorithm>
#include "PathNode.h"
#include "Log.h"

PathSearcher::PathSearcher(){
}

//AStar探索？
void PathSearcher::searchShortestPath(PathNode &start,PathNode &goal){
	m_start = &start;
	m_goal = &goal;
	
	std::vector<PathNode *> list;
	
	start.found=true;
	start.cost= 0;
	start.from = NULL;
	list.push_back(&start);
	
	while(list.size()>0){
		std::vector<PathNode *>::iterator begin = list.begin();
		PathNode *node = *list.begin();
		list.erase(list.begin(),list.begin()+1);
		
		if(node==&goal)return;

		std::vector<PathNode *> neighbors = node->neighbors();
		for(std::vector<PathNode *>::iterator it = neighbors.begin();it!=neighbors.end();it++){
			if((*it)->found)continue;
			
			(*it)->found=true;
			(*it)->cost = node->cost + 1;
			(*it)->from = node;

			list.push_back(*it);
		}
		
		std::sort(list.begin(),list.end(),PathSearchPred());
	}

	return;	
}

PathSearcher::~PathSearcher(){
}

PathNode *PathSearcher::start() const{
	return m_start;
}

PathNode *PathSearcher::goal() const{
	return m_goal;
}

bool PathSearcher::found() const{
	return m_goal && m_goal->from != NULL;
}

std::vector<PathNode *> PathSearcher::foundPath() const{
	std::vector<PathNode *>path;
	if(!found())return path;
	for(PathNode *node = goal();
			node!=NULL;
			node = node->from){
		path.insert(path.begin(),node);
	}
	return path;
}

