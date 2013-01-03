#include "Viewer.h"

std::string Viewer::printWorld(const Maze &maze,const Mouse *mouse) const{
	std::string str;

	for(int y=0;y<maze.height();y++){
		for(int x=0;x<maze.width();x++){
			str.append("+");
			Cell cell=maze.constCellAt(Point(x,y));
			str.append(cell.topWall()?"---":"   ");
		}
		str.append("+\n");
		for(int x=0;x<maze.width();x++){
			Point p(x,y);
			Cell cell=maze.constCellAt(p);
			str.append(cell.leftWall()?"|":" ");
		
			if(mouse && mouse->pos().equals(p)){
				switch(mouse->direction()){
					case DirectionLeft:
						str.append("<=-");
						break;
					case DirectionTop:
						str.append("/|\\");
						break;
					case DirectionRight:
						str.append("-=>");
						break;
					case DirectionBottom:
						str.append("\\|/");
						break;
				}
			}else if(maze.start().equals(p)){
				str.append(" S ");
			}else if(maze.goal().equals(p)){
				str.append(" G ");
			}else{
				str.append("   ");
			}			
		}
		str.append("|\n");
	}
	for(int x=0;x<maze.width();x++){
		str.append("+---");
	}
	str.append("+\n");

	return str;
}
