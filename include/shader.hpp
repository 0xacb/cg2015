#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/glew.h>
#endif

using namespace std;

class Shader {
	public:
		Shader();
		~Shader();
		void compileShaders();
		void loadProgram();
		bool load(const char *path);
		void printLog(GLuint obj);
		char* vertexProgram;
		char* fragmentProgram;
		GLuint vertexShader, fragmentShader, shaderProgram;
};
