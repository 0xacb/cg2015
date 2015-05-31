#include "Sphere.hpp"

Sphere::Sphere() {

}

void Sphere::render() {
  glEnable(GL_COLOR_MATERIAL);
  glColor3f(0.8f, 0.5f, 0.3f);
  gluSphere(gluNewQuadric(), 1.0f, 24, 24);
  glDisable(GL_COLOR_MATERIAL);
};
