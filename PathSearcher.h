#pragma once
#include<stdio.h>
#include<vector>
class PathNode;

//コンストラクタでAStar探索を実行する
//もう一度検索するにはreleaseを呼んでください。
class PathSearcher{
	private:
		PathNode *m_start;
		PathNode *m_goal;
	public:
		PathSearcher();
		virtual ~PathSearcher();
		virtual void release();

		PathNode *start() const;
		PathNode *goal() const;
		bool found() const;

		virtual void searchShortestPath(PathNode &start,PathNode &goal);
		std::vector<PathNode *>foundPath() const;
};

