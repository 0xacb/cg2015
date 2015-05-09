#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <stdio.h>

#include "object.hpp"

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

using namespace std;

class Sphere : public Object {
  public:
		explicit Sphere(const char* path) : Object(path) { }
    void render();
};

#endif
