#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <stdio.h>
#include <GL/glut.h>

#include "main.hpp"
#include "object.hpp"

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

using namespace std;

class Sphere : public Object {
	private:
  public:
		GLfloat vx, vy, vz;
		GLfloat radius;
		Sphere(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _radius);
		GLfloat color[4] = {0.0, 0.2, 1.0, 1.0};
		void update();
    void render();
		bool isColliding(Sphere *otherSphere);
};

#endif
