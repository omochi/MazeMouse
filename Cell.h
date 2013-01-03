#pragma once

#include <stdio.h>
#include "Direction.h"


class Cell{
	private:
		//このセルの左に壁があるか
		bool m_leftWall;
		//このセルの上に壁があるか
		bool m_topWall;
	public:
		Cell();
		Cell(bool leftWall,bool topWall);
		bool leftWall() const;
		bool topWall() const;
		bool existsWall(Direction d) const;

		Cell cellBySetWall(Direction d,bool exists)const;
};



