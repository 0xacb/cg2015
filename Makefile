all: main

CC = g++
CFLAGS = -lGL -lGLU -lglfw -std=c++11 -Wall -g
LDFLAGS = -lm

object.o: object.cpp object.hpp
	${CC} ${CFLAGS} -c object.cpp

camera.o: camera.cpp camera.hpp
	${CC} ${CFLAGS} -c camera.cpp

world.o: world.cpp world.hpp
	${CC} ${CFLAGS} -c world.cpp

texture.o: texture.cpp texture.hpp
	${CC} ${CFLAGS} -c texture.cpp

skybox.o: skybox.cpp skybox.hpp
	${CC} ${CFLAGS} -c skybox.cpp

main: main.o object.o camera.o world.o texture.o skybox.o
	${CC} ${CFLAGS} main.o object.o camera.o world.o texture.o skybox.o ${LDFLAGS} -o main

clean:
	rm *.o
