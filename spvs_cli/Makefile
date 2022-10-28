CC = g++
CFLAGS = -std=c++17
SRC = src/simple_scanner.cpp
INCLUDES = -ISFML/include -Iinclude
SRC = src/simple_scanner.cpp
LIBS = -L SFML/build/lib -lsfml-network
LINKER = -Wl,-rpath,./SFML/build/lib

bin/spvs: src/simple_scanner.cpp
	$(CC) $(CFLAGS) src/simple_scanner.cpp -o bin/spvs $(INCLUDES) $(LIBS) $(LINKER)

clean:
	rm bin/*
