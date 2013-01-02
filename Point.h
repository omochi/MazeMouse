#pragma once

class Point{
	public:
		int x;
		int y;
		Point();
		Point(int x,int y);
		bool equals(const Point &point) const;
};

