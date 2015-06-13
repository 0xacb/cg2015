#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <stdio.h>
#include <math.h>

#include "main.hpp"
#include "object.hpp"

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glew.h>
	#include <GL/glu.h>
#endif

using namespace std;

class Particle {
  private:
  public:
    GLfloat x, y, z;
    GLfloat vx, vy, vz;
};

#endif
