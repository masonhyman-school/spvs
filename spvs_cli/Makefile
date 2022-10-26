CC = g++
CFLAGS = -std=c++17
SRC = src/main.cpp
INCLUDES = -I SFML/include -I include
LIBS = -L SFML/build/lib -lsfml-network
LINKER = -Wl,-rpath,./SFML/build/lib

bin/spvs: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o bin/spvs $(INCLUDES) $(LIBS) $(LINKER)

clean:
	rm bin/*
