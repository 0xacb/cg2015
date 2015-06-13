#include "sphere.hpp"

Sphere::Sphere(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _radius, GLfloat _r, GLfloat _g, GLfloat _b) {
	x = _x;
	y = _y;
	z = _z;
	radius = _radius;

	float speedCap = 0.02;
	vx = randomFloat(-speedCap, speedCap);
	vy = randomFloat(-speedCap, speedCap);
	vz = randomFloat(-speedCap, speedCap);

	if (_r == -1) {
		color[0] = randomFloat(0.0, 1.0);
		color[1] = randomFloat(0.0, 1.0);
		color[2] = randomFloat(0.0, 1.0);
	} else {
		color[0] = _r;
		color[1] = _g;
		color[2] = _b;
	}

	color[3] = 1.0f;
}

void Sphere::update() {
	x += vx;
	y += vy;
	z += vz;
}

void Sphere::render() {
	GLfloat colorWhite[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat colorAmbient[4] = {0.2, 0.2, 0.2, 1.0};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	gluSphere(gluNewQuadric(), radius, 24, 24);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorWhite);
	glMaterialfv(GL_FRONT, GL_AMBIENT, colorAmbient);
};

bool Sphere::isColliding(Sphere *otherSphere) {
	float centerDistance = sqrt(pow(x - otherSphere->x, 2) + pow(y - otherSphere->y, 2) + pow(z - otherSphere->z, 2));

	float sumRadius = radius + otherSphere->radius;

	return centerDistance < sumRadius;
}
