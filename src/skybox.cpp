#include "skybox.hpp"

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

void Skybox::initShaders() {
  sunShader.load("shaders/sun_vert.glsl");
  sunShader.load("shaders/sun_frag.glsl");
  sunShader.compileShaders();
  sunShader.loadProgram();
  this->lightYLoc = glGetUniformLocation(this->sunShader.shaderProgram, "lightY");

  lensShader.load("shaders/lens_vert.glsl");
  lensShader.load("shaders/lens_frag.glsl");
  lensShader.compileShaders();
  lensShader.loadProgram();
  this->lightYLensLoc = glGetUniformLocation(this->lensShader.shaderProgram, "lightY");
  this->currentLenLoc = glGetUniformLocation(this->lensShader.shaderProgram, "currentLen");
  this->brightnessLoc = glGetUniformLocation(this->lensShader.shaderProgram, "brightness");
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
  if (rSun > 200) {
    return MIN_BRIGHTNESS;
  }
  if (rSun < 60) {
    return fmin(rSun/60.0+MIN_BRIGHTNESS, 1.0);
  }
  if (rSun < 130) {
    return 1;
  }
  if (rSun < 200) {
    return fmin(-(rSun-200)*(1.0/50)+MIN_BRIGHTNESS, 1.0);
  }
  return 1;
}

void Skybox::draw(double dist) {
  this->brightness = calcDayBrightness(rSun+90);
  glDisable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  for (int i=0;i<6;i++) {
    drawSkyboxFace(i, textures[i], dist, brightness);
  }
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void drawCircle(float r) {
  float delta = 0.1;
  glBegin(GL_POLYGON);
    for(float angle=0;angle<2*PI;angle+=delta) {
      glVertex3f(r*cos(angle), 0, r*sin(angle));
    }
  glEnd();
}

void drawFlare(float r, bool circle) {
  float delta = 0.1;
  glBegin(GL_POLYGON);
  if (circle) {
    for(float angle=0;angle<2*PI;angle+=delta) {
      glVertex3f(r*cos(angle), r*sin(angle), 0.0);
    }
  }
  else {
    for(float angle=0;angle<6;angle+=1) {
      glVertex3f(r*cos(angle), r*sin(angle), 0.0);
    }
  }
  glEnd();
}

void Skybox::renderLensFlare(float windowWidth, float windowHeight) {
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  GLdouble sun2dX, sun2dY, sun2dZ;

  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetIntegerv(GL_VIEWPORT, viewport);

  gluProject(lightX, lightY, lightZ, modelview, projection, viewport, &sun2dX, &sun2dY, &sun2dZ);

  float windowCenterX = windowWidth * 0.5f;
  float windowCenterY = windowHeight * 0.5f;

  if (sun2dZ > 1.0) {
    return;
  }
  if ((sun2dX < -40.0) || (sun2dX > windowWidth+40.0)) {
    return;
  }
  if ((sun2dY < -40.0) || (sun2dY > windowHeight+40.0)) {
    return;
  }

  float intensity = windowWidth-sqrt(pow(sun2dX-windowCenterX, 2)+pow(sun2dY-windowCenterY, 2));
  intensity = intensity/windowWidth;

  glLoadIdentity();
  float ratio = windowWidth/windowHeight;
  glOrtho(0, windowWidth, 0, windowHeight, -1, 2);

  float dx = windowCenterX-sun2dX;
  float dy = windowCenterY-sun2dY;
  dx *= ratio;
  dy *= ratio;
  float len = sqrt(dx * dx + dy * dy);

  float vx = dx/len;
  float vy = dy/len;

  dx = vx*len*0.1f;
  dy = vy*len*0.1f;

  glUseProgram(this->lensShader.shaderProgram);

  glUniform1f(this->lightYLensLoc, lightY);
  glUniform1f(this->brightnessLoc, pow(intensity, 9)*brightness*brightness);

  glPushMatrix();
    glTranslatef(sun2dX, sun2dY, 0);
    glTranslatef(4*dx, 4*dy, 0);
    for (int i=nLens;i>=0;i--) {
      glUniform1f(this->currentLenLoc, float(i));
      glPushMatrix();
        glTranslatef(3*dx*i, 0.4*dy*i, 0);
        glScalef(ratio, 1.0, 1.0);
        drawFlare(i*3, !(i%2));
      glPopMatrix();
    }
  glPopMatrix();

  glUseProgram(0);
}

float radSun;

void Skybox::renderSun(double delta) {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glPushMatrix();
    glRotatef(rSun, 0.0, 0.0, 1.0);
    rSun += delta*360/dayDuration;
    rSun = fmod(rSun, 360);

    glTranslatef(sunX, sunY, sunZ);

    glUseProgram(this->sunShader.shaderProgram);
    radSun = TO_RADS(rSun);
    lightX = -sunY*sin(radSun);
    lightY = sunY*cos(radSun);
    glUniform1f(this->lightYLoc, lightY);

    drawCircle(25);

    glUseProgram(0);

    GLfloat lightAmbient[4] = {0.5, 0.5, 0.5, 1.0};
    GLfloat lightPosition[4] = {sunX, sunY, sunZ, 0.0};
    GLfloat lightDiffuse[4] = {brightness, brightness, brightness, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glPopMatrix();
}
