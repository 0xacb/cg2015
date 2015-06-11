varying vec4 viewCoords;
varying vec4 texCoords;

uniform sampler2D base;
uniform sampler2D reflection;

void main() {
	vec4 projCoord = viewCoords / viewCoords.q;
	projCoord = (projCoord + 1.0) * 0.5;
	projCoord = clamp(projCoord, 0.0001, 0.9999);
	vec4 reflectionColor = texture2D(reflection, projCoord.xy);
	vec4 baseColor = texture2D(base, texCoords.xy);
	baseColor = baseColor*0.2;
	reflectionColor = reflectionColor-0.7;
	vec4 waterColor = vec4(0.0, 0.45, 0.7, 1.0);
	gl_FragColor = waterColor+baseColor+reflectionColor;
}
