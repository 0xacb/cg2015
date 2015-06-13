#ifndef SPHERE_HPP
#define SPHERE_HPP

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

class Sphere : public Object {
	private:
  public:
		GLfloat vx, vy, vz;
		GLfloat radius;
		Sphere(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _radius, GLfloat _r, GLfloat _g, GLfloat _b);
		GLfloat color[4];
		void update();
		void render();
		bool isColliding(Sphere *otherSphere);
};

#endif
