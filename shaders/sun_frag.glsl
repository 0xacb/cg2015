varying vec4 vertCoords;

uniform float lightY;

void main(void) {
	float alpha = 1.0;
	if ((abs(vertCoords.x) > 10.0) || (abs(vertCoords.z) > 10.0)) {
		alpha = 1.0-sqrt(vertCoords.x*vertCoords.x+vertCoords.z*vertCoords.z)/23.0;
		alpha = alpha*3.0;
	}
	float red = 1.0;
	float green = lightY/400.0+0.6;
	float blue = (alpha-0.01)*lightY/400.0;
	vec4 color = vec4(red, green, blue, alpha);
	gl_FragColor = color;
}
