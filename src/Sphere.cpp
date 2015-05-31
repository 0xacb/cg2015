#include "Sphere.hpp"

Sphere::Sphere() {
  
}

void Sphere::render() {
  glColor3f(1.0f, 0.5f, 0.0f);
  gluSphere(gluNewQuadric(), 1.0f, 24, 24);
};
