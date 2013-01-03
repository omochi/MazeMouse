CFLAGS += -Wall -Wextra -Werror
LIBS += -lncurses
OBJS = 	Point.o \
		Direction.o \
		Cell.o \
		Maze.o \
		Mouse.o \
		PathNode.o \
		PathSearcher.o \
		MazeCellNode.o \
		MazePathSearcher.o \
		Viewer.o 	

all : MazeView ManualMouse

MazeView : MazeView.o  $(OBJS) 
	$(CXX) $(CFLAGS) $(LDFLAGS) MazeView.o $(OBJS) $(LIBS) -o $@.out

ManualMouse : ManualMouse.o $(OBJS)
	$(CXX) $(CFLAGS) $(LDFLAGS) ManualMouse.o $(OBJS) $(LIBS) -o $@.out

clean :
	rm -f *.o *.out

