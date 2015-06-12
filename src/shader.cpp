#include <shader.hpp>

Shader::Shader(){}

Shader::~Shader(){}

void Shader::compileShaders() {
	if (this->vertexProgram) {
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->vertexShader, 1, &this->vertexProgram, NULL);
		glCompileShader(this->vertexShader);
		free(this->vertexProgram);
		printLog(this->vertexShader);
	}
	if (this->fragmentProgram) {
		this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->fragmentShader, 1, &this->fragmentProgram, NULL);
		glCompileShader(this->fragmentShader);
		free(this->fragmentProgram);
		printLog(this->fragmentShader);
	}
}

void Shader::loadProgram() {
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragmentShader);
	glLinkProgram(this->shaderProgram);
	printLog(this->shaderProgram);
	glUseProgram(this->shaderProgram);
}

void Shader::printLog(GLuint obj) {
	int infoLength = 0;
	char info[1024];

	if (glIsShader(obj)) {
		glGetShaderInfoLog(obj, 1024, &infoLength, info);
	}
	else {
		glGetProgramInfoLog(obj, 1024, &infoLength, info);
	}

	if (infoLength)
	printf("%s\n", info);
}

bool Shader::load(const char *path) {
	FILE *f;
	long len, end;
	char *str;
	f = fopen(path, "r");
	
	if (!f) {
		return false;
	}

	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	str = (char*)malloc(len*sizeof(char));
	end = fread(str, sizeof(char), len, f);
	str[end] = '\0';

	fclose(f);
	if (strstr(path, "vert")) {
		this->vertexProgram = str;
		return true;
	}
	else if (strstr(path, "frag")) {
		this->fragmentProgram = str;
		return true;
	}
	else return false;
}
