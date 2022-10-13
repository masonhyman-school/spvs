CC = g++
CFLAGS = -std=c++17
SRC = src/main.cpp src/simple_scanner.cpp
INCLUDES = -I SFML/include
LIBS = -L SFML/build/lib -lsfml-network
LINKER = -Wl,-rpath,./SFML/build/lib

bin/spvs: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o bin/spvs $(INCLUDES) $(LIBS) $(LINKER)

clean:
	rm bin/*
