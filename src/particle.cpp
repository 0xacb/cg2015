#include "particle.hpp"

Particle::Particle(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _vx, GLfloat _vy, GLfloat _vz) {
  x = _x;
  y = _y;
  z = _z;

  vx = _vx;
  vy = _vy;
  vz = _vz;

  lifeTime = 100.0f;

  GLfloat color[] = {1.0f, 0.0f, 0.0f, 1.0f};
}

void Particle::update() {
  x += vx;
  y += vy;
  z += vz;
}

void Particle::render() {
  glBegin(GL_POLYGON);
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
}
