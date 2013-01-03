#include "Maze.h"
#include "Cell.h"
#include "Point.h"

Maze::Maze(int width,int height):m_width(width),m_height(height),
	m_cells(std::vector<Cell>(width*height)){
}
int Maze::width() const{
	return m_width;
}
int Maze::height() const{
	return m_height;
}
const Point &Maze::start() const{
	return m_start;
}
void Maze::setStart(const Point &p){
	m_start=p;
}
const Point &Maze::goal() const{
	return m_goal;
}
void Maze::setGoal(const Point &p){
	m_goal=p;
}
Cell &Maze::cellAt(const Point &pos){
	return m_cells[pos.y*m_width+pos.x];
}
const Cell &Maze::constCellAt(const Point &pos) const{
	return m_cells[pos.y*m_width+pos.x];
}
bool Maze::isInside(const Point &p) const{
	return (0<=p.x && p.x<m_width && 0<=p.y && p.y<m_height);
}

//こういうの気持ち良い
bool Maze::existsWall(const Point &p,Direction d) const{
	switch(d){
		case DirectionLeft:
		case DirectionTop:
			if(isInside(p)){
				return constCellAt(p).existsWall(d);
			}
			return true;		
			break;
		case DirectionRight:
		case DirectionBottom:
			return existsWall(p.neighbor(d),DirectionReverse(d));
	}
}
void Maze::setWall(const Point &p,Direction d,bool exists){
	switch(d){
		case DirectionLeft:
		case DirectionTop:
			if(isInside(p)){
				cellAt(p)=cellAt(p).cellBySetWall(d,exists);
			}
			break;
		case DirectionRight:
		case DirectionBottom:
			return setWall(p.neighbor(d),DirectionReverse(d),exists);
	}
}


Maze *Maze::load(std::istream &data){
	std::string line;
	char buf[256];
	int width,height;
	
	//読み捨て
	if(!std::getline(data,line))return NULL;
	//サイズ
	if(!std::getline(data,line))return NULL;
	width=atoi(line.c_str());
	if(!std::getline(data,line))return NULL;
	height=atoi(line.c_str());
	
	if(!data)return NULL;
	
	Maze *maze = new Maze(width,height);
	
	for(int y=0;y<height;y++){
		if(!std::getline(data,line))goto fail;
		
		line.copy(buf,sizeof(buf)-1,0);
		char *token=strtok(buf," ");
		for(int x=0;x<width;x++){
			Point pos=Point(x,y);
			if(token==NULL)goto fail;
			int value=strtol(token,NULL,16);

			Cell cell(value & 0x8,value & 0x1);
			
			maze->cellAt(pos)=cell;
			
			token=strtok(NULL," ");
		}
	}

	//データファイルにはスタートとゴールかかれてないらしい。
	//とりあえずデフォルトの場所をルールに合わせて設定するようにする。
	
	maze->setStart(Point(0,height-1));
	maze->setGoal(Point(width/2,height/2));


	return maze;

fail:
	fprintf(stderr,"maze data load error\n");
	delete maze;
	return NULL;
}

std::string Maze::toString() const{
	char buf[256];
	std::string str;
	snprintf(buf,sizeof(buf),"size:%dx%d\n",m_width,m_height);
	str.append(buf);
	
	for(int y=0;y<m_height;y++){
		for(int x=0;x<m_width;x++){
			Cell cell=constCellAt(Point(x,y));
			if(cell.topWall()){
				str.append("+---");
			}else{
				str.append("+   ");
			}
		}
		str.append("+\n");
		for(int x=0;x<m_width;x++){
			Point pos=Point(x,y);
			Cell cell=constCellAt(pos);
			if(cell.leftWall()){
				str.append("|");
			}else{
				str.append(" ");
			}
			if(m_start.equals(pos)){
				str.append(" S ");
			}else if(m_goal.equals(pos)){
				str.append(" G ");
			}else{
				str.append("   ");
			}
		}
		str.append("|\n");
	}
	for(int x=0;x<m_width;x++){
		str.append("+---");
	}
	str.append("+\n");

	return str;
}
