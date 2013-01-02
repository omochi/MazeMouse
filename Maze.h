#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <string>


#include "Point.h"
#include "Cell.h"

class Maze{
	//C++のフィールドってプレフィックス付けないとローカル変数と衝突しませんか？
	private:
		int m_width;
		int m_height;
		std::vector<Cell> m_cells;
		Point m_start;
		Point m_goal;
	public:
		Maze(int width,int height);
		
		int width() const;
		int height() const;
		
		const Point &start() const;	
		void setStart(const Point &p);
		const Point &goal() const;
		void setGoal(const Point &p);
		
		Cell &cellAt(const Point &pos);
		const Cell &constCellAt(const Point &pos) const;

		std::string toString() const;

		static Maze *load(std::istream &data);
		

};
