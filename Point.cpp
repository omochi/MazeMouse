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
