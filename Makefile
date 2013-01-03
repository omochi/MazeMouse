CFLAGS += -Wall -Wextra -Werror
OBJS = 	Point.o \
		Direction.o \
		Cell.o \
		Maze.o \
		Mouse.o \
		Viewer.o \

all : MazeView ManualMouse

MazeView : MazeView.o  $(OBJS) 
	$(CXX) $(CFLAGS) MazeView.o $(OBJS) -o $@.out

ManualMouse : ManualMouse.o $(OBJS)
	$(CXX) $(CFLAGS) ManualMouse.o $(OBJS) -o $@.out

clean :
	rm -f *.o *.out

