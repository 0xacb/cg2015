#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/glew.h>
#endif

int loadTexture(const char * path);
