#include "camera.hpp"

Camera::Camera(){}

Camera::~Camera(){}

void Camera::move(double delta, float seaLevel) {
	x += vcamX*camSpeed*delta;
	y += vcamY*camSpeed*delta;
	z += vcamZ*camSpeed*delta;

	if (y < seaLevel) {
		y = seaLevel;
	}

	glLoadIdentity();
	glRotatef(rcamX, 1.0f, 0.0f, 0.0f);
	glRotatef(rcamY, 0.0f, 1.0f, 0.0f);
	glTranslatef(-x, -y, -z);
}

void Camera::rotate(int horizontalMovement, int verticalMovement) {
	rcamX += verticalMovement*mouseVSensitivity/1000;
	rcamY += horizontalMovement*mouseHSensitivity/1000;

	if (rcamX < -90.0f) {
		rcamX = -90.0f;
	}
	if (rcamX > 90.0f)  {
		rcamX = 90.0f;
	}
	if (rcamY < -180.0f) {
		rcamY += 360.0f;
	}
	if (rcamY > 180.0f) {
		rcamY -= 360.0f;
	}

	float pitchFactor = cos(TO_RADS(rcamX));
	lastCamMovementXComponent = (camSpeed * float(sin(TO_RADS(rcamY)))) * pitchFactor;
	lastCamMovementYComponent = camSpeed * float(sin(TO_RADS(rcamX))) * -1.0f;
	float yawFactor = float(cos(TO_RADS(rcamX)));
	lastCamMovementZComponent = (camSpeed * float(cos(TO_RADS(rcamY))) * -1.0f) * yawFactor;
}

void Camera::calcMovement(map<int, bool> keyState) {
	float pitchFactor, yawFactor, yRotRad;

	camMovementXComponent = 0.0f;
	camMovementYComponent = 0.0f;
	camMovementZComponent = 0.0f;

	if (keyState[GLFW_KEY_SPACE]) {
		camMovementYComponent += 3;
	}

	if (keyState[GLFW_KEY_LEFT_CONTROL]) {
		camMovementYComponent -= 3;
	}

	if (keyState[GLFW_KEY_W]) {
		pitchFactor = cos(TO_RADS(rcamX));
		camMovementXComponent += (camSpeed * float(sin(TO_RADS(rcamY)))) * pitchFactor;
		camMovementYComponent += camSpeed * float(sin(TO_RADS(rcamX))) * -1.0f;
		yawFactor = float(cos(TO_RADS(rcamX)));
		camMovementZComponent += (camSpeed * float(cos(TO_RADS(rcamY))) * -1.0f) * yawFactor;
	}

	if (keyState[GLFW_KEY_S]) {
		pitchFactor = cos(TO_RADS(rcamX));
		camMovementXComponent += (camSpeed * float(sin(TO_RADS(rcamY))) * -1.0f) * pitchFactor;
		camMovementYComponent += camSpeed * float(sin(TO_RADS(rcamX)));
		yawFactor = float(cos(TO_RADS(rcamX)));
		camMovementZComponent += (camSpeed * float(cos(TO_RADS(rcamY)))) * yawFactor;
	}

	if (keyState[GLFW_KEY_A]) {
		yRotRad = TO_RADS(rcamY);
		camMovementXComponent += -camSpeed * float(cos(yRotRad));
		camMovementZComponent += -camSpeed * float(sin(yRotRad));
	}

	if (keyState[GLFW_KEY_D]) {
		yRotRad = TO_RADS(rcamY);
		camMovementXComponent += camSpeed * float(cos(yRotRad));
		camMovementZComponent += camSpeed * float(sin(yRotRad));
	}

	vcamX = camMovementXComponent;
	vcamY = camMovementYComponent;
	vcamZ = camMovementZComponent;

	if (vcamX > camSpeed) vcamX = camSpeed;
	else if (vcamX < -camSpeed) vcamX = -camSpeed;
	if (vcamY > camSpeed) vcamY = camSpeed;
	else if (vcamY < -camSpeed) vcamY = -camSpeed;
	if (vcamZ > camSpeed) vcamZ = camSpeed;
	else if (vcamZ < -camSpeed) vcamZ = -camSpeed;
}
