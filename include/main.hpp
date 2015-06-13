#ifndef MAIN_HPP
#define MAIN_HPP

#ifdef __APPLE__
  #include <OpenGL/glu.h>
  #include <OpenGL/gl.h>
#else
  #include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

float randomFloat(float a, float b);
void print_vector(vector<int> *vec);

#endif
