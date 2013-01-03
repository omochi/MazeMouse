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

		virtual std::vector<PathNode *> nodeNeighbors(const PathNode &node)= 0;
		//推定残りコスト
		virtual int nodeEstimatedRemainingCost(const PathNode &node)= 0;	

		//実コストと推定残りコストを合わせて比較
		static bool nodeLessEstimatedScore(const PathNode &left,const PathNode &right);	
};

class PathSearchPred{
	private:
		PathSearcher &m_searcher;
	public:
		PathSearchPred(PathSearcher &searcher);
		bool operator()(const PathNode *left,const PathNode *right);
};
