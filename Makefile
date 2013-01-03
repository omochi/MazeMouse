CFLAGS += -Wall -Wextra -Werror
OBJS = MazeMouse.o \
	   Point.o \
	   Direction.o \
	   Cell.o \
	   Maze.o \


MazeMouse : $(OBJS) 
	$(CXX) $(CFLAGS) $(OBJS) -o $@
clean :
	rm -f *.o 
