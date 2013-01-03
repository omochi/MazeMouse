#include "Mouse.h"

Mouse::Mouse(const Maze &physicalMaze):
	m_physicalMaze(&physicalMaze),
	m_learnedMaze(new Maze(physicalMaze.width(),physicalMaze.height())){
	
	m_pos=physicalMaze.start();	
	m_direction=DirectionTop;
	m_learnedMaze->setStart(physicalMaze.start());
	m_learnedMaze->setGoal(physicalMaze.goal());
}

Mouse::~Mouse(){
	delete m_learnedMaze;
}

void Mouse::learnMaze(){
	bool wall = m_physicalMaze->existsWall(m_pos,m_direction);
	m_learnedMaze->setWall(m_pos,m_direction,wall);
}

const Point &Mouse::pos() const{
	return m_pos;
}
Direction Mouse::direction() const{
	return m_direction;
}
const Maze &Mouse::learnedMaze() const{
	return *m_learnedMaze;
}

void Mouse::goStraight(){
	if(!m_physicalMaze->existsWall(m_pos,m_direction)){
		//壁がなければ進めます
		m_pos=m_pos.neighbor(m_direction);
	}
	learnMaze();
}
void Mouse::turnLeft(){
	m_direction=DirectionRotate(m_direction,DirectionLeft);
	learnMaze();
}
void Mouse::turnRight(){
	m_direction=DirectionRotate(m_direction,DirectionRight);
	learnMaze();
}


