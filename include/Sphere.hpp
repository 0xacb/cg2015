#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <stdio.h>
#include <math.h>

#include "main.hpp"
#include "object.hpp"

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif

using namespace std;

class Sphere : public Object {
	private:
  public:
		GLfloat vx, vy, vz;
		GLfloat radius;
		Sphere(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _radius);
		GLfloat color[4];
		void update();
    void render();
		bool isColliding(Sphere *otherSphere);
};

#endif
