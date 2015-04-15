#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <vector>

#include "world.hpp"

#define NAME "GG 2015"

using namespace std;

int TIMER_INTERVAL = 17;

GLint WORLD_WIDTH = 1600;
GLint WORLD_HEIGHT = 1200;

GLint WINDOW_WIDTH = 800;
GLint WINDOW_HEIGHT = 600;
GLint WINDOW_POSITION_X = 290;
GLint WINDOW_POSITION_Y = 50;

GLfloat camX = 0, camY = 0, camZ = -5;

World world;

void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(TIMER_INTERVAL, update, 1);
}

void initG(void) {
	glClearColor(0, 0, 0, 1);

	glViewport(0,0, 400, 300);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 0,0,0, 0,1,0);
}

void addLights() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightpos[4] = {0.0, 15.0, -10.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
}

void checkKeys() {

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);

	for (int i=0;i<(signed)world.objects.size();i++) {
		world.objects[i].render();
	}

	glRotatef(-1.5, 0, 1, 0);

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow(NAME);
	glutIgnoreKeyRepeat(true);

	initG();

	world.load("obj/monkey.obj");
	addLights();

	glutDisplayFunc(display);
	glutTimerFunc(TIMER_INTERVAL, update, 1);

	glutMainLoop();
	return 1;
}
