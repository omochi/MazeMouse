#pragma once

#include <stdio.h>
#include "Point.h"
#include "Direction.h"
#include "Maze.h"

class Mouse{
	//パズル的に特に意味はないけど、
	//もともとロボット制御の話しらしいので、
	//雰囲気を出すために無駄に向きを導入する
	//しかもこのネズミは目の前の壁の有無しか判定不能
	//前進と方向転換のみ可能
	private:
		//ネズミが居る迷路
		const Maze * const m_physicalMaze;
		
		//場所
		Point m_pos;
		//向き
		Direction m_direction;

		//ネズミが認識した迷路
		//未知壁と壁無しを分けたほうがいいんだろうか
		//とりあえずわけない
		Maze * const m_learnedMaze;

		void learnMaze();
	public:
		Mouse(const Maze &physicalMaze);
		virtual ~Mouse();
		const Point &pos() const;
		Direction direction() const;

		const Maze &learnedMaze() const;

		//制御
		void goStraight();
		//一発で反対側を向くのは無理とする
		void turnRight();
		void turnLeft();	
};
