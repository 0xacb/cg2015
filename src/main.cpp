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

using namespace std;

GLint WINDOW_RESOLUTION_X = 700;
GLint WINDOW_RESOLUTION_Y = 500;
GLint WINDOW_MID_X = WINDOW_RESOLUTION_X/2;
GLint WINDOW_MID_Y = WINDOW_RESOLUTION_Y/2;

double WORLD_SIZE = 1000;

bool AUTOMATIC_RESOLUTION = true;
bool FULLSCREEN = false;
GLint MULTISAMPLING_LEVEL = 4;
GLint FIELD_OF_VIEW = 90;

GLFWwindow* window;
map<int, bool> keyState;
int nFrames = 0;

World world;

/*Input*/
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
  int horizMovement = (mouseX - WINDOW_MID_X) * 2;
  int vertMovement  = (mouseY - WINDOW_MID_Y) * 2;
  world.camera.rotate(horizMovement, vertMovement);
  glfwSetCursorPos(window, WINDOW_MID_X, WINDOW_MID_Y);
}

void initInputs() {
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetCursorPos(window, WINDOW_MID_X, WINDOW_MID_Y);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

/*Window*/
void initG(void) {
  glClearColor(0, 0, 0, 1);

  glViewport(0,0, WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FIELD_OF_VIEW, 1.0*WINDOW_RESOLUTION_X/WINDOW_RESOLUTION_Y, 0.1, WORLD_SIZE*2);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void initWindow() {
  if (!glfwInit())
  exit(EXIT_FAILURE);
  glfwWindowHint(GLFW_SAMPLES, MULTISAMPLING_LEVEL);

  /*Automatic resolution*/
  if (AUTOMATIC_RESOLUTION) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    WINDOW_RESOLUTION_X = mode->width;
    WINDOW_RESOLUTION_Y = mode->height;
  }

  window = glfwCreateWindow(WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y, WINDOW_NAME, FULLSCREEN ? glfwGetPrimaryMonitor() : NULL, NULL);
  //glfwGetPrimaryMonitor() - fullscreen
  if (!window)
  exit(EXIT_FAILURE);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0); //1 => lock FPS to Screen Hz
  glShadeModel(GL_SMOOTH);
}

/*Main Loop*/
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
    world.skybox.draw(world.size);
    world.skybox.renderSun(delta);
    world.render();
    world.camera.calcMovement(keyState);
    world.camera.move(delta);

    glfwSwapBuffers(window);
    glfwPollEvents();

    oldTime = currentTime;
  }
}

int main(int argc, char **argv) {
  initWindow();
  initInputs();
  initG();

  world.size = WORLD_SIZE;
  world.load("obj/dust2.obj", 0, 0, 0);

  for (int x = 0; x < 5; x++) {
    for (int z = 0; z < 5; z++) {
      world.load(new Sphere(), x * 3, 5, z * 3);
    }
  }

  world.skybox.load("skyboxes/bluesky1");

  mainLoop();
  exit(EXIT_FAILURE);
}
