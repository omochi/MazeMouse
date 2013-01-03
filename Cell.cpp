#include "Cell.h"

Cell::Cell():m_leftWall(false),m_topWall(false){
}
Cell::Cell(bool leftWall,bool topWall):m_leftWall(leftWall),m_topWall(topWall){
}
bool Cell::leftWall() const{
	return m_leftWall;
}
bool Cell::topWall() const{
	return m_topWall;
}
bool Cell::existsWall(Direction d) const{
	switch(d){
		case DirectionLeft:		return m_leftWall;
		case DirectionTop:		return m_topWall;
		default:
			fprintf(stderr,"invalid direction in %s\n",__PRETTY_FUNCTION__);
			return false;
	}
}
Cell Cell:cellBySetWall(Direction d,bool exists){
	switch(d){
		case DirectionLeft:return Cell(exists,topWall());
		case DirectionTop:return Cell(leftWall(),exists);
		default:
			fprintf(stderr,"invalid direction in %s\n",__PRETTY_FUNCTION__);
			return Cell();
	}
}
