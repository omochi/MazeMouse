#include "Point.h"

Point::Point():x(0),y(0){
}
Point::Point(int _x,int _y):x(_x),y(_y){

}
bool Point::equals(const Point &point) const{
	return x==point.x && y==point.y;
}
