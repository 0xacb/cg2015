#include <stdio.h>
#include <GL/gl.h>
#define BACK "back"
#define FRONT "front"
#define LEFT "left"
#define RIGHT "right"
#define BOTTOM "bottom"
#define TOP "top"
#define EXTENSION "bmp"

using namespace std;

class Skybox {
	public:
		Skybox();
		~Skybox();
		GLuint textures[6];
		bool load(const char* path);
		void draw(double D);
		void renderSun();
};
