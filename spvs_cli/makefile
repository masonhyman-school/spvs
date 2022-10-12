OBJS	= spvs.o
SOURCE	= spvs.cpp
HEADER	= spvs.h
OUT	= spvs
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

spvs.o: spvs.cpp
	$(CC) $(FLAGS) spvs.cpp 


clean:
	rm -f $(OBJS) $(OUT)
