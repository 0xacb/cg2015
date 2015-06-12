#include "sea.hpp"

Sea::Sea(){}

Sea::~Sea(){}

void Sea::initShaders() {
	shader.load("shaders/sea_vert.glsl");
	shader.load("shaders/sea_frag.glsl");
	shader.compileShaders();
	shader.loadProgram();

	this->baseLoc = glGetUniformLocation(this->shader.shaderProgram, "base");
	this->reflectionLoc = glGetUniformLocation(this->shader.shaderProgram, "reflection");
	this->waveWidthLoc = glGetUniformLocation(shader.shaderProgram, "waveWidth");
	this->waveHeightLoc = glGetUniformLocation(shader.shaderProgram, "waveHeight");
	this->wavePeriodLoc = glGetUniformLocation(shader.shaderProgram, "wavePeriod");
	this->lightPosLoc = glGetUniformLocation(shader.shaderProgram, "lightPos");
	this->cameraPosLoc = glGetUniformLocation(shader.shaderProgram, "cameraPos");
}

void Sea::load(GLint textureWidth, GLint textureHeight) {
	this->textureImage = (unsigned char*)malloc(4*textureWidth*textureHeight*sizeof(char));
	glGenTextures(1, &reflectionTexture);
	glBindTexture(GL_TEXTURE_2D, reflectionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	this->texture = loadTexture("obj/textures/sea.bmp");
}

void Sea::renderReflection(GLint textureWidth, GLint textureHeight) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, reflectionTexture);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, textureWidth, textureHeight);
	glDisable(GL_TEXTURE_2D);
}

float lightX, lightY, lightZ = 0;

void Sea::render(double delta, Camera camera, float rSun, float sunY) {
	register int i, j;
	glUseProgram(this->shader.shaderProgram);

	rSun = TO_RADS(rSun);
	lightX = -(0*cos(rSun) - sunY*sin(rSun));
	lightY = sunY*cos(rSun) + 0*sin(rSun);

	glUniform1f(this->waveWidthLoc, waveWidth);
	glUniform1f(this->waveHeightLoc, waveHeight);
	glUniform1f(this->wavePeriodLoc, wavePeriod);
	glUniform4f(this->lightPosLoc, lightX, lightY, lightZ, 1.0f);
	glUniform4f(this->cameraPosLoc, camera.x, camera.y, camera.z, 1.0f);
	glUniform1i(this->baseLoc, 0);
	glUniform1i(this->reflectionLoc, 1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->reflectionTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	glBegin(GL_QUADS);
	for (i=-this->xSize;i<this->xSize;i+=this->divSize) {
		for (j=-this->ySize;j<this->ySize;j+=this->divSize) {
			glTexCoord2f(0.0, 0.0); glVertex3f(i, this->seaLevel, j);
			glTexCoord2f(0.0, 1.0); glVertex3f(i, this->seaLevel, j+this->divSize);
			glTexCoord2f(1.0, 1.0); glVertex3f(i+this->divSize, this->seaLevel, j+this->divSize);
			glTexCoord2f(1.0, 0.0); glVertex3f(i+this->divSize, this->seaLevel, j);
		}
	}
	glEnd();

	this->wavePeriod += this->waveFreq;
	glUseProgram(0);
}
