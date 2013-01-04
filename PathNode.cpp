#include "PathNode.h"
#include "PathSearcher.h"
PathNode::PathNode(PathSearcher &_searcher):searcher(_searcher),
	found(false),cost(0),from(NULL){
}
PathNode::~PathNode(){
}
int PathNode::estimatedRemainingCost() const{
	return 0;
}
int PathNode::estimatedScore() const{
	return cost + estimatedRemainingCost();
}

bool PathSearchPred::operator()(const PathNode *left,const PathNode *right){
	return left->estimatedScore() < right->estimatedScore();
}
