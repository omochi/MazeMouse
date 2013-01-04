#include "Point.h"

Point::Point():x(0),y(0){
}
Point::Point(int _x,int _y):x(_x),y(_y){

}
bool Point::equals(const Point &point) const{
	return x==point.x && y==point.y;
}
Point Point::neighbor(Direction d) const{
	switch(d){
		case DirectionLeft:		return Point(x-1,y);
		case DirectionTop:		return Point(x,y-1);
		case DirectionRight:	return Point(x+1,y);
		case DirectionBottom:	return Point(x,y+1);
		default:
			fprintf(stderr,"invalid direction in %s\n",__PRETTY_FUNCTION__);
			return Point();
	}
}

Direction Point::directionTo(const Point &p) const{
	if(p.x < x)return DirectionLeft;
	if(p.y < y)return DirectionTop;
	if(p.x > x)return DirectionRight;
	if(p.y > y)return DirectionBottom;
	return DirectionLeft;
}

bool Point::operator<(const Point &p) const{
	if(y != p.y)return y<p.y;
	return x < p.x;
}

std::string Point::toString() const{
	char buf[256];
	snprintf(buf,sizeof(buf),"(%d,%d)",x,y);
	return std::string(buf);
}
