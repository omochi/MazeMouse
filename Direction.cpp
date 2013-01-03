#include "Direction.h"

Direction DirectionReverse(Direction d){
	switch(d){
		case DirectionLeft:return DirectionRight;
		case DirectionTop:return DirectionBottom;
		case DirectionRight:return DirectionLeft;
		case DirectionBottom:return DirectionTop;
		default:
			fprintf(stderr,"invalid direction in %s\n",__PRETTY_FUNCTION__);
			return DirectionLeft;
	}
}
