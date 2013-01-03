#include "Mouse.h"

Mouse::Mouse(const Maze &physicalMaze):m_physhicalMaze(&physicalMaze),
	m_learnedMaze(new Maze(physicalMaze.width(),physicalMaze.height())){
	
	m_pos=Point(0,0);
	m_direction=DirectionTop;
}

Mouse::~Mouse(){
	delete m_learnedMaze;
}

void Mouse::learnMaze(){
	bool wall = m_physicalMaze->existsWall(m_pos,m_direction);
	m_learnedMaze->setWall(m_pos,m_direction,wall);
}

const Pos &Mouse::pos() const{
	return m_pos;
}
Direction Mouse::direction() const{
	return m_direction;
}
const Maze * Mouse::learnedMaze() const{
	return m_learnedMaze;
}

void Maze::goFront(){
	if(!m_physicalMaze->existsWall(m_pos,m_direction)){
		//壁がなければ進めます
		m_pos=m_pos.neighbor(m_direction);
	}
	learnMaze();
}
void Maze::turnLeft(){
	m_direction=DirectionRotate(m_direction,DirectionLeft);
	learnMaze();
}
void Maze::turnRight(){
	m_direction=DirectionRotate(m_direction,DirectionRight);
	learnMaze();
}


