CC = g++
CFLAGS = -std=c++17
SRC = src/main.cpp
INCLUDES = -ISFML/include -Iinclude
LIBS = -L SFML/build/lib -lsfml-network
LINKER = -Wl,-rpath, ./SFML/build/lib

bin/spvs: src/main.cpp
	$(CC) $(CFLAGS) $(SRC) -o bin/spvs $(INCLUDES) $(LIBS) $(LINKER)

clean:
	rm bin/*
