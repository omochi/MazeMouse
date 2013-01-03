CFLAGS += -Wall -Wextra -Werror
OBJS = Point.o \
	   Direction.o \
	   Cell.o \
	   Maze.o \


all : MazeView

MazeView : MazeView.o  $(OBJS) 
	$(CXX) $(CFLAGS) MazeView.o $(OBJS) -o $@
clean :
	rm -f *.o 
