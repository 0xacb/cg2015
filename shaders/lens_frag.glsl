#version 130

varying vec4 vertCoords;

uniform float lightY;
uniform float currentLen;
uniform float brightness;

void main(void) {
	float alpha = (6.0-currentLen)/5.0;
	alpha = clamp(alpha, 0.3, 0.6);

	float red = 1.0;
	float green = lightY/400.0+0.6;
	float blue = lightY/400.0-0.1;
	
	int curLen = int(currentLen);

	if (curLen % 5 == 0) {
		green = green-0.9;
		blue = blue-0.9;
	}
	else if (curLen % 4 == 0) {
		blue = blue-0.8;
	}
	else if (curLen % 3 == 0) {
		red = 0.1;
		blue = blue-0.9;
	}
	else if (curLen % 2 == 0) {
		red = 0.2;
		green = green-0.2;
		blue = 0.9;
	}

	alpha = clamp(brightness*alpha, 0.0, 0.8)*2.0;

	vec4 color = vec4(red, green, blue, alpha);
	gl_FragColor = color;
}
