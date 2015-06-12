#include <stdio.h>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/glew.h>
#endif

#include "math.hpp"
#include "camera.hpp"
#include "skybox.hpp"
#include "texture.hpp"

#define TEXTURE_SIZE 768

using namespace std;

class Sea {
	public:
		Sea();
		~Sea();
		Shader shader;
		GLfloat seaLevel = 0.6;
		GLfloat waveWidth = 1.5, waveHeight = 0.2, waveFreq = 0.04, wavePeriod = 0.5;
		GLint baseLoc, reflectionLoc, waveWidthLoc, waveHeightLoc, wavePeriodLoc, lightPosLoc, cameraPosLoc;
		GLuint texture, reflectionTexture;
		int xSize = 60, ySize = 60, divSize = 5;
		unsigned char* textureImage;
		void initShaders();
		void load(GLint textureWidth, GLint textureHeight);
		void render(double delta, Camera camera, float rSun, float sunY);
		void renderReflection(GLint textureWidth, GLint textureHeight);
};
