#include <string.h>
#include "skybox.hpp"
#include "texture.hpp"

Skybox::Skybox(){}

Skybox::~Skybox(){}

bool Skybox::load(const char* path){
    int i;
    char tokens[6][7] = {FRONT, RIGHT, BACK, LEFT, TOP, BOTTOM};
    char tpath[100];
    for (i=0;i<6;i++) {
        sprintf(tpath, "%s-%s.%s", path, tokens[i], EXTENSION);
        textures[i] = loadTexture(tpath);
        if (textures[i] == 0)
            return false;
    }

    return true;
}

void Skybox::draw(double D) {
	glColor3f(1, 1, 1);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
	glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
	glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
	glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
	glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
	glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
	glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
	glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
	glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
	glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
	glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
	glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
	glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-D,+D,-D);
	glTexCoord2f(1,0); glVertex3f(+D,+D,-D);
	glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
	glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
	glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
	glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
	glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Skybox::renderSun() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	GLfloat lightAmbient[4]= {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[4] = {-100.0, 100.0, -100.0, 1.0};
	GLfloat lightDiffuse[4]= {1.0f, 1.0f, 1.0f, 100.0f};
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
}
