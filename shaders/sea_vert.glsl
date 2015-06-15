varying vec4 viewCoords;
varying vec4 texCoords;
varying vec4 vertCoords;

uniform float waveWidth;
uniform float waveHeight;
uniform float wavePeriod;

uniform vec4 lightPos, cameraPos;

void main() {
	vec4 v = vec4(gl_Vertex);
	float waveR = max(abs(v.z), abs(v.x))*0.01;
	v.y = sin(waveWidth*v.x + wavePeriod) * cos(waveWidth*v.z + wavePeriod) * waveHeight + waveR*2.0;
	viewCoords = gl_ModelViewProjectionMatrix * v;
	gl_Position = viewCoords;
	texCoords = gl_MultiTexCoord0;
	vertCoords = v;
}
