CFLAGS += -Wall -Wextra -Werror
OBJS = 	Point.o \
		Direction.o \
		Cell.o \
		Maze.o \
		Mouse.o \
		Viewer.o \


all : MazeView

MazeView : MazeView.o  $(OBJS) 
	$(CXX) $(CFLAGS) MazeView.o $(OBJS) -o $@

ManualMouse : ManualMouse.o $(OBJS)
	$(CXX) $(CFLAGS) ManualMouse.o $(OBJS) -o $@

clean :
	rm -f *.o 
