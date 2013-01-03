CFLAGS += -Wall -Wextra -Werror
OBJS = 	Point.o \
		Direction.o \
		Cell.o \
		Maze.o \
		Mouse.o \
		Viewer.o \

all : MazeView ManualMouse

MazeView : MazeView.o  $(OBJS) 
	$(CXX) $(CFLAGS) MazeView.o $(OBJS) -o $@.app

ManualMouse : ManualMouse.o $(OBJS)
	$(CXX) $(CFLAGS) ManualMouse.o $(OBJS) -o $@.app

clean :
	rm -f *.o 
