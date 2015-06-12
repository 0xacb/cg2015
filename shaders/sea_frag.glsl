varying vec4 viewCoords;
varying vec4 texCoords;
varying vec4 vertCoords;

uniform sampler2D base;
uniform sampler2D reflection;

uniform vec4 lightPos, cameraPos;

void main() {
	const float kShine = 64.0;
	float waveSpecular = vertCoords.y+2.0;

	vec4 projCoord = viewCoords / viewCoords.q;
	projCoord = (projCoord+1.0) * 0.5;
	projCoord = clamp(projCoord, 0.00001, 0.99999);
	vec4 reflectionColor = texture2D(reflection, projCoord.xy);
	reflectionColor = reflectionColor-0.7;

	vec4 baseColor = texture2D(base, texCoords.xy);
	baseColor = baseColor*0.2;

	vec4 waterColor = vec4(0.0, 0.45, 0.7, 1.0);

	//sun reflection
	vec4 eyeDirection = normalize(cameraPos - vertCoords);
	vec4 toEye = normalize(cameraPos-vertCoords);
	vec4 nlightPos = normalize(-lightPos-cameraPos);
	vec4 lightReflection = normalize(reflect(nlightPos, eyeDirection)); 
	float intensity = max(0.0, dot(lightReflection, toEye));
	vec4 specular = vec4(pow(intensity, kShine));

	specular = specular*waveSpecular*0.15;
	specular = specular*vec4(2.0, 2.0, 1.0, 1.0);

	float lightY = lightPos.y;
	float red = 1.0;
	float green = lightY/400.0+0.5;
	float blue = lightY/400.0;
	specular = specular*vec4(red, green, blue, 1.0);

	vec4 color = waterColor+baseColor+reflectionColor+specular;
	color = color*vec4(1.4, 1.0, 1.0, 1.0);

	gl_FragColor = color;
}
