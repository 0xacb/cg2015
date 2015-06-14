#include "particle.hpp"

Particle::Particle(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _vx, GLfloat _vy, GLfloat _vz) {
  x = _x;
  y = _y;
  z = _z;

  vx = _vx;
  vy = _vy;
  vz = _vz;

  lifeTime = 100.0f;

  float selector = randomFloat(0, 1);

  if (selector < 0.3) {
    color[0] = randomFloat(0.8, 1.0);
    color[1] = 0.0f;
    color[2] = 0.0f;
  } else if (selector > 0.3 && selector < 0.5) {
    color[0] = randomFloat(0.8, 1.0);
    color[1] = randomFloat(0.8, 1.0);
    color[2] = 0.0f;
  } else {
    color[0] = 1.0f;
    color[1] = randomFloat(0.4, 0.6);
    color[2] = 0.0f;
  }
}

void Particle::update() {
  x += vx;
  y += vy;
  z += vz;

  color[3] -= 0.005f;
}

void Particle::render() {
  GLfloat colorWhite[4] = {1.0, 1.0, 1.0, 1.0};
  GLfloat colorAmbient[4] = {0.2, 0.2, 0.2, 1.0};

  glMaterialfv(GL_FRONT, GL_DIFFUSE, this->color);
  glMaterialfv(GL_FRONT, GL_AMBIENT, this->color);

  glBegin(GL_POLYGON);
  glNormal3f( 0.0, 1.0, 1.0);
  glVertex3f(  0.1, -0.1, 0.1 );
  glVertex3f(  0.1,  0.1, 0.1 );
  glVertex3f( -0.1,  0.1, 0.1 );
  glVertex3f( -0.1, -0.1, 0.1 );
  glEnd();

  // Purple side - RIGHT
  glBegin(GL_POLYGON);
  glVertex3f( 0.1, -0.1, -0.1 );
  glVertex3f( 0.1,  0.1, -0.1 );
  glVertex3f( 0.1,  0.1,  0.1 );
  glVertex3f( 0.1, -0.1,  0.1 );
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
  glVertex3f( -0.1, -0.1,  0.1 );
  glVertex3f( -0.1,  0.1,  0.1 );
  glVertex3f( -0.1,  0.1, -0.1 );
  glVertex3f( -0.1, -0.1, -0.1 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
  glVertex3f(  0.1,  0.1,  0.1 );
  glVertex3f(  0.1,  0.1, -0.1 );
  glVertex3f( -0.1,  0.1, -0.1 );
  glVertex3f( -0.1,  0.1,  0.1 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glVertex3f(  0.1, -0.1, -0.1 );
  glVertex3f(  0.1, -0.1,  0.1 );
  glVertex3f( -0.1, -0.1,  0.1 );
  glVertex3f( -0.1, -0.1, -0.1 );
  glEnd();

  glMaterialfv(GL_FRONT, GL_DIFFUSE, colorWhite);
  glMaterialfv(GL_FRONT, GL_AMBIENT, colorAmbient);
}
