#pragma once

#include<vector>

class PathNode{
	public:
		bool found;
		int cost;
		PathNode *from;
		PathNode();		
		virtual ~PathNode();
};
