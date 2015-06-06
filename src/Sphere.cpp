#include "Sphere.hpp"

Sphere::Sphere() {

}

void Sphere::render() {
	GLfloat colorBlue[4] = {0.1, 0.3, 1.0, 1.0};
	GLfloat colorWhite[4] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorBlue);
	gluSphere(gluNewQuadric(), 1.0f, 24, 24);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorWhite);
};
