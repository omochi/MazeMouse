CFLAGS += -Wall -Wextra -Werror
LDFLAGS += -lncurses
OBJS = 	Point.o \
		Direction.o \
		Cell.o \
		Maze.o \
		Mouse.o \
		Viewer.o \

all : MazeView ManualMouse

MazeView : MazeView.o  $(OBJS) 
	$(CXX) $(CFLAGS) $(LDFLAGS) MazeView.o $(OBJS) -o $@.out

ManualMouse : ManualMouse.o $(OBJS)
	$(CXX) $(CFLAGS) $(LDFLAGS) ManualMouse.o $(OBJS) -o $@.out

clean :
	rm -f *.o *.out

