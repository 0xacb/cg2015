#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <stdio.h>
#include <GL/glut.h>

#include "object.hpp"

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

using namespace std;

class Sphere : public Object {
	private:
		GLfloat radius;

  public:
		Sphere(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _radius);
    void render();
		bool isColliding(Sphere *otherSphere);
};

#endif
