#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
  #include <OpenGL/glu.h>
  #include <OpenGL/gl.h>
#else
	#include <GL/glu.h>
	#include <GL/gl.h>
#endif

#include <math.h>
#include <vector>
#include <map>

#include "world.hpp"

#define WINDOW_NAME "GG 2015"

#define KEY_UP 87
#define KEY_DOWN 83
#define KEY_LEFT 65
#define KEY_RIGHT 68

#define PI atan(1) * 4
#define TO_RADS(deg) deg*PI/180

using namespace std;

GLint WINDOW_WIDTH = 700;
GLint WINDOW_HEIGHT = 500;
GLint WINDOW_MID_X = WINDOW_WIDTH /2;
GLint WINDOW_MID_Y = WINDOW_HEIGHT/2;

GLint MULTISAMPLING_LEVEL = 2;

World world;

GLFWwindow* window;
map<int, bool> keyState;

GLfloat camSpeed = 2.5f;
GLfloat mouseVSensitivity = 10.0f;
GLfloat mouseHSensitivity = 10.0f;
GLfloat camX = 0, camY = 1.5, camZ = -5;
GLfloat vcamX = 1, vcamY = 1, vcamZ = 1;
GLfloat rcamX = 0, rcamY = 0, rcamZ = 0;

void addLights() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightpos[4] = {0.0, 15.0, -10.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
}

/*Inputs*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE) {
		exit(EXIT_SUCCESS);
	}
	if (action == GLFW_PRESS) {
		keyState[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		keyState[key] = false;
	}
}

void mouse_callback(GLFWwindow *window, GLdouble mouseX, GLdouble mouseY) {
    int horizMovement = mouseX - WINDOW_MID_X;
    int vertMovement  = mouseY - WINDOW_MID_Y;

    rcamX += vertMovement*mouseVSensitivity/1000;
    rcamY += horizMovement*mouseHSensitivity/1000;

    if (rcamX < -90.0f) {
        rcamX = -90.0f;
    }
    if (rcamX > 90.0f)  {
        rcamX = 90.0f;
    }
	if (rcamY < -180.0f) {
        rcamY += 360.0f;
    }
    if (rcamY > 180.0f) {
        rcamY -= 360.0f;
    }
    glfwSetCursorPos(window, WINDOW_MID_X, WINDOW_MID_Y);
}

void initInputs() {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetCursorPos(window, WINDOW_MID_X, WINDOW_MID_Y);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

/*Window*/
void initG(void) {
	glClearColor(0, 0, 0, 1);

	glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 1.0*WINDOW_WIDTH/WINDOW_HEIGHT, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 0,0,0, 0,1,0);
}

void initWindow() {
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_SAMPLES, MULTISAMPLING_LEVEL);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL); //glfwGetPrimaryMonitor() - fullscreen
	if (!window)
		exit(EXIT_FAILURE);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0); //1 => lock FPS to Screen Hz
	glShadeModel(GL_SMOOTH);
}

/*Main Loop*/
void calculateCameraMovement() {
	float camMovementXComponent = 0.0f;
	float camMovementYComponent = 0.0f;
	float camMovementZComponent = 0.0f;

	if (keyState[KEY_UP]) {
		float pitchFactor = cos(TO_RADS(rcamX));
		camMovementXComponent += (camSpeed * float(sin(TO_RADS(rcamY)))) * pitchFactor;
		camMovementYComponent += camSpeed * float(sin(TO_RADS(rcamX))) * -1.0f;
		float yawFactor = float(cos(TO_RADS(rcamX)));
		camMovementZComponent += ( camSpeed * float(cos(TO_RADS(rcamY))) * -1.0f ) * yawFactor;
	}

	if (keyState[KEY_DOWN]) {
		float pitchFactor = cos(TO_RADS(rcamX));
		camMovementXComponent += (camSpeed * float(sin(TO_RADS(rcamY))) * -1.0f) * pitchFactor;
		camMovementYComponent += camSpeed * float(sin(TO_RADS(rcamX)));
		float yawFactor = float(cos(TO_RADS(rcamX)));
		camMovementZComponent += (camSpeed * float(cos(TO_RADS(rcamY)))) * yawFactor;
	}

	if (keyState[KEY_LEFT]) {
		float yRotRad = TO_RADS(rcamY);
		camMovementXComponent += -camSpeed * float(cos(yRotRad));
		camMovementZComponent += -camSpeed * float(sin(yRotRad));
	}

	if (keyState[KEY_RIGHT]) {
		float yRotRad = TO_RADS(rcamY);
		camMovementXComponent += camSpeed * float(cos(yRotRad));
		camMovementZComponent += camSpeed * float(sin(yRotRad));
	}

	vcamX = camMovementXComponent;
	vcamY = camMovementYComponent;
	vcamZ = camMovementZComponent;

	if (vcamX > camSpeed) vcamX = camSpeed;
	else if (vcamX < -camSpeed) vcamX = -camSpeed;
	if (vcamY > camSpeed) vcamY = camSpeed;
	else if (vcamY < -camSpeed) vcamY = -camSpeed;
	if (vcamZ > camSpeed) vcamZ = camSpeed;
	else if (vcamZ < -camSpeed) vcamZ = -camSpeed;
}

void moveCamera(double delta) {
	camX += vcamX*delta;
	camY += vcamY*delta;
	camZ += vcamZ*delta;
	glLoadIdentity();
	glRotatef(rcamX, 1.0f, 0.0f, 0.0f);
    glRotatef(rcamY, 0.0f, 1.0f, 0.0f);
    glTranslatef(-camX, -camY, -camZ);
}

int nFrames = 0;
void mainLoop() {
	double oldTime = glfwGetTime(), oldFrameTime = glfwGetTime();
	double currentTime, delta, deltaFrame;
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*Delta*/
		currentTime = glfwGetTime();
		delta = (currentTime-oldTime);
		deltaFrame = (currentTime-oldFrameTime);
		nFrames++;
		if (deltaFrame >= 1.0) {

			printf("\r%d FPS", nFrames);
			fflush(stdout);
			nFrames = 0;
			oldFrameTime = currentTime;
		}

		/*Draw*/
		world.render();
		calculateCameraMovement();
		moveCamera(camSpeed*delta);

		glfwSwapBuffers(window);
		glfwPollEvents();

		oldTime = currentTime;
	}
}

int main(int argc, char **argv) {
	initWindow();
	initInputs();
	initG();

	world.load("obj/dei.obj");
	addLights();

	mainLoop();
	exit(EXIT_FAILURE);
}
