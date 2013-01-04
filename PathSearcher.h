#pragma once
#include<stdio.h>
#include<vector>
class PathNode;

//コンストラクタでAStar探索を実行する
class PathSearcher{
	private:
		PathNode *m_start;
		PathNode *m_goal;
	protected:
		//継承先のコンストラクタで呼んで
		void searchShortestPath(PathNode &start,PathNode &goal);
	public:
		PathSearcher();
		virtual ~PathSearcher();

		PathNode *start() const;
		PathNode *goal() const;
		bool found() const;
		std::vector<PathNode *>foundPath() const;
};

