#include <string.h>
#include <math.h>
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

void drawSkyboxFace(int i, GLint texture, double dist, float brightness) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(brightness, brightness, brightness);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
    if (i==0) {
        glTexCoord2f(0,0); glVertex3f(-dist,-dist,-dist);
        glTexCoord2f(1,0); glVertex3f(+dist,-dist,-dist);
        glTexCoord2f(1,1); glVertex3f(+dist,+dist,-dist);
        glTexCoord2f(0,1); glVertex3f(-dist,+dist,-dist);
    }
    else if (i==1) {
        glTexCoord2f(0,0); glVertex3f(+dist,-dist,-dist);
        glTexCoord2f(1,0); glVertex3f(+dist,-dist,+dist);
        glTexCoord2f(1,1); glVertex3f(+dist,+dist,+dist);
        glTexCoord2f(0,1); glVertex3f(+dist,+dist,-dist);
    }
    else if (i==2) {
        glTexCoord2f(0,0); glVertex3f(+dist,-dist,+dist);
        glTexCoord2f(1,0); glVertex3f(-dist,-dist,+dist);
        glTexCoord2f(1,1); glVertex3f(-dist,+dist,+dist);
        glTexCoord2f(0,1); glVertex3f(+dist,+dist,+dist);
    }
    else if (i==3) {
        glTexCoord2f(0,0); glVertex3f(-dist,-dist,+dist);
        glTexCoord2f(1,0); glVertex3f(-dist,-dist,-dist);
        glTexCoord2f(1,1); glVertex3f(-dist,+dist,-dist);
        glTexCoord2f(0,1); glVertex3f(-dist,+dist,+dist);
    }
    else if (i==4) {
        glTexCoord2f(0,0); glVertex3f(-dist,+dist,-dist);
        glTexCoord2f(1,0); glVertex3f(+dist,+dist,-dist);
        glTexCoord2f(1,1); glVertex3f(+dist,+dist,+dist);
        glTexCoord2f(0,1); glVertex3f(-dist,+dist,+dist);
    }
    else if (i==5) {
        glTexCoord2f(1,1); glVertex3f(+dist,-dist,-dist);
        glTexCoord2f(0,1); glVertex3f(-dist,-dist,-dist);
        glTexCoord2f(0,0); glVertex3f(-dist,-dist,+dist);
        glTexCoord2f(1,0); glVertex3f(+dist,-dist,+dist);
    }
	glEnd();
}

float calcDayBrightness(float rSun) {
    rSun = fmod(rSun, 360);
    if (rSun > 180) {
        return MIN_BRIGHTNESS;
    }
    if (rSun < 60) {
        return rSun/60.0+MIN_BRIGHTNESS;
    }
    if (rSun < 130) {
        return 1;
    }
    if (rSun < 180) {
        return -(rSun-180)*(1.0/50)+MIN_BRIGHTNESS;
    }
    return 1;
}

void Skybox::draw(double dist) {
    float brightness = calcDayBrightness(rSun+90);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        for (int i=0;i<6;i++) {
            drawSkyboxFace(i, textures[i], dist, brightness);
        }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Skybox::renderSun(double delta) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glPushMatrix();
		glRotatef(rSun, 0.0, 0.0, 1.0);
		rSun += delta*360/dayDuration;
        rSun = fmod(rSun, 360);
        GLfloat lightAmbient[4]= {1.0, 1.0, 1.0, 1.0};
        GLfloat lightPosition[4] = {sunX, sunY, sunZ, 1.0};
        GLfloat lightDiffuse[4]= {1.0, 1.0, 1.0, 100.0};
        glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

		glTranslatef(sunX, sunY, sunZ);
        glBegin(GL_QUADS);
			glVertex3f(10, 0, 10);
			glVertex3f(0, 0, 10);
			glVertex3f(0, 0, 0);
			glVertex3f(10, 0, 0);
		glEnd();
	glPopMatrix();
}
