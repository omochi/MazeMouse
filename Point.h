#pragma once

#include <stdio.h>
#include <string>
#include "Direction.h"

class Point{
	public:
		int x;
		int y;
		Point();
		Point(int x,int y);
		bool equals(const Point &point) const;
		Point neighbor(Direction d)const;
		Direction directionTo(const Point &p)const;
		bool operator<(const Point &p) const;
		std::string toString() const;
};

