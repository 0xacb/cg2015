varying vec4 vertCoords;

void main() {
	vertCoords = vec4(gl_Vertex);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
