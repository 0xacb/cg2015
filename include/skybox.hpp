#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glew.h>
#endif

#include "shader.hpp"
#include "texture.hpp"
#include "math.hpp"

#define BACK "back"
#define FRONT "front"
#define LEFT "left"
#define RIGHT "right"
#define BOTTOM "bottom"
#define TOP "top"
#define EXTENSION "bmp"
#define MIN_BRIGHTNESS 0.1

using namespace std;

class Skybox {
	public:
		Skybox();
		~Skybox();
		Shader sunShader;
		Shader lensShader;
		float rSun = 0, sunX = 0, sunY = 400, sunZ = 0, lightX, lightY, lightZ = 0;
		float dayDuration = 1000; //seconds
		float brightness;
		float nLens = 5;
		GLint lightYLoc, lightYLensLoc, currentLenLoc, brightnessLoc;
		GLint textures[6];
		void initShaders();
		bool load(const char* path);
		void draw(double dist);
		void renderSun(double delta);
		void renderLensFlare(float windowWidth, float windowHeight);
};
