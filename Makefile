all: main

CC = g++
CFLAGS = -Wall -lGL -lGLU -lglfw -std=c++11 -g
LDFLAGS = -lm

object.o: object.cpp object.hpp
	${CC} ${CFLAGS} -c object.cpp

world.o: world.cpp world.hpp
	${CC} ${CFLAGS} -c world.cpp

main: main.o object.o world.o
	${CC} ${CFLAGS} main.o object.o world.o ${LDFLAGS} -o main

clean:
	rm *.o
