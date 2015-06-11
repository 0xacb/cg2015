#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __APPLE__
  #include <OpenGL/glu.h>
  #include <OpenGL/gl.h>
#else
  #include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include <math.h>
#include <vector>
#include <map>

#include "main.hpp"
#include "world.hpp"

#define WINDOW_NAME "GG 2015"

using namespace std;

GLint WINDOW_RESOLUTION_X = 1366;
GLint WINDOW_RESOLUTION_Y = 768;
GLint WINDOW_MID_X = WINDOW_RESOLUTION_X/2;
GLint WINDOW_MID_Y = WINDOW_RESOLUTION_Y/2;

bool AUTOMATIC_RESOLUTION = true;
bool FULLSCREEN = true;
GLint MULTISAMPLING_LEVEL = 4;
GLint FIELD_OF_VIEW = 90;

GLFWwindow* window;
map<int, bool> keyState;
int nFrames = 0;

World world;

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

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
  gluPerspective(FIELD_OF_VIEW, 1.0*WINDOW_RESOLUTION_X/WINDOW_RESOLUTION_Y, 0.1, world.size*2);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
  if (!window)
  exit(EXIT_FAILURE);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0); //1 => lock FPS to Screen Hz
  glShadeModel(GL_SMOOTH);
}

double delta;

void renderScene() {
  world.skybox.draw(world.size);
  world.skybox.renderSun(delta);
  world.render();
}

void renderReflection() {
  glPushMatrix();
      glScalef(1.0, -0.9, 1.0);
      glTranslatef(0.0, -world.sea.seaLevel, 0.0);
      double plane[4] = {0.0, 1.0, 0.0, -world.sea.seaLevel}; 
      glEnable(GL_CLIP_PLANE0);
      glClipPlane(GL_CLIP_PLANE0, plane);
      renderScene();
      world.sea.renderReflection(WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);
      glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
}

/*Main Loop*/
void mainLoop() {
  double oldTime = glfwGetTime(), oldFrameTime = glfwGetTime();
  double currentTime, deltaFrame;

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*Delta*/
    currentTime = glfwGetTime();
    delta = (currentTime-oldTime);
    deltaFrame = (currentTime-oldFrameTime);
    nFrames++;

    /* Update scene elements */
    world.update();

    /*Draw*/
    renderReflection();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    world.sea.render(delta);
    renderScene();
  
    world.camera.calcMovement(keyState);
    world.camera.move(delta);

    glfwSwapBuffers(window);
    glfwPollEvents();

    oldTime = currentTime;
  }
}

void initShaders() {
  world.sea.initShaders();
}

int main(int argc, char **argv) {
  initWindow();
  initInputs();
  initG();
  glewInit();
  initShaders();

  srand(time(NULL));
  for (GLfloat x = 0; x < 9; x++) {
    for (GLfloat z = 0; z < 9; z++) {
      string type("sphere");
      world.load(new Sphere(x * 6, 30, z * 6, 2), type);
    }
  }

  world.load("obj/island.obj", 0, 0, 0, 1.0);
  world.load("obj/box.obj", 0, 0, 0, 0.6);
  world.skybox.load("skyboxes/bluesky1");
  world.sea.load(WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);

  mainLoop();
  exit(EXIT_FAILURE);
}
