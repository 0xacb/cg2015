#include "camera.hpp"

Camera::Camera(){}

Camera::~Camera(){}

void Camera::move(double delta) {
	camX += vcamX*camSpeed*delta;
	camY += vcamY*camSpeed*delta;
	camZ += vcamZ*camSpeed*delta;
	glLoadIdentity();
	glRotatef(rcamX, 1.0f, 0.0f, 0.0f);
	glRotatef(rcamY, 0.0f, 1.0f, 0.0f);
	glTranslatef(-camX, -camY, -camZ);
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

}

void Camera::calcMovement(map<int, bool> keyState) {
	float camMovementXComponent = 0.0f;
	float camMovementYComponent = 0.0f;
	float camMovementZComponent = 0.0f;

	if (keyState[GLFW_KEY_SPACE]) {
		camMovementYComponent += 3;
	}

	if (keyState[GLFW_KEY_W]) {
		float pitchFactor = cos(TO_RADS(rcamX));
		camMovementXComponent += (camSpeed * float(sin(TO_RADS(rcamY)))) * pitchFactor;
		camMovementYComponent += camSpeed * float(sin(TO_RADS(rcamX))) * -1.0f;
		float yawFactor = float(cos(TO_RADS(rcamX)));
		camMovementZComponent += ( camSpeed * float(cos(TO_RADS(rcamY))) * -1.0f ) * yawFactor;
	}

	if (keyState[GLFW_KEY_S]) {
		float pitchFactor = cos(TO_RADS(rcamX));
		camMovementXComponent += (camSpeed * float(sin(TO_RADS(rcamY))) * -1.0f) * pitchFactor;
		camMovementYComponent += camSpeed * float(sin(TO_RADS(rcamX)));
		float yawFactor = float(cos(TO_RADS(rcamX)));
		camMovementZComponent += (camSpeed * float(cos(TO_RADS(rcamY)))) * yawFactor;
	}

	if (keyState[GLFW_KEY_A]) {
		float yRotRad = TO_RADS(rcamY);
		camMovementXComponent += -camSpeed * float(cos(yRotRad));
		camMovementZComponent += -camSpeed * float(sin(yRotRad));
	}

	if (keyState[GLFW_KEY_D]) {
		float yRotRad = TO_RADS(rcamY);
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
