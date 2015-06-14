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
		GLfloat lifeTime;
		GLfloat color[4] = {1.0f, 0.0f, 0.0f, 0.5f};

		Particle(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
		void update();
		void render();
};

#endif
