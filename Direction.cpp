#include "Direction.h"

Direction DirectionReverse(Direction d){
	return DirectionRotate(d,DirectionBottom);
}
Direction DirectionRotateLeft(Direction d){
	switch(r){
		case DirectionLeft:return DirectionBottom;
		case DirectionTop:return DirectionLeft;
		case DirectionRight:return DirectionTop;
		case DirectionBottom:return DirectionRight;
	}
}
Direction DirectionRotate(Direction d,Direction r){
	int n;
	switch(r){
		case DirectionLeft:
			n=1;
			break;
		case DirectionTop:
			n=0;
			break;
		case DirectionRight:
			n=3;
			break;
		case DirectionBottom:
			n=2;
			break;
	}
	for(int i=0;i<n;i++)d=DirectionRotateLeft(d);
	return d;
}
