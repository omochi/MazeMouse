#pragma once

#include<vector>

class PathSearcher;

class PathNode{
	public:
		PathSearcher &searcher;
		bool found;
		int cost;
		PathNode *from;
		PathNode(PathSearcher &_searcher);	
		virtual ~PathNode();
		virtual std::vector<PathNode *> neighbors() = 0;
		//推定残りコスト
		virtual int estimatedRemainingCost() const;
		int estimatedScore() const;
};

class PathSearchPred{
	public:
		bool operator()(const PathNode *left,const PathNode *right);
};

