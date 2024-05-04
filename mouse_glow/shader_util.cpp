#pragma once

#include <iostream>
#include <fstream>

#define GLEW_STATIC
#include <GL\glew.h>

#include "shader_util.h"

void DestroyShaders(ShaderInfo*);

static const GLchar* ReadShader(const char* filename) {
	// Abre o ficheiro 'filename' em bin�rio, e coloca-se na �ltima posi��o do ficheiro.
	std::ifstream file(filename, std::ifstream::ate, std::ifstream::binary);

	if (file.is_open()) {
		std::streampos file_size = file.tellg();

		// Reposiciona a leitura do ficheiro no seu in�cio.
		file.seekg(0, std::ios::beg);

		GLchar* source = new GLchar[int(file_size)];

		file.read(source, file_size);

		// Fecha a string.
		source[file_size] = 0;

		file.close();

		// Retorna o endere�o da string alocada.
		return const_cast<const GLchar*>(source);
	}
	else std::cerr << "Error opening the file \"" << filename << "\"" << std::endl;

	return nullptr;
}

GLuint LoadShaders(ShaderInfo* shaders) {
	if (shaders == nullptr) return 0;

	GLuint program = glCreateProgram();

	for (GLuint i = 0; i < shaders[i].type != GL_NONE; i++) {
		// Criar um objeto shader
		shaders[i].shader = glCreateShader(shaders[i].type);

		const GLchar* source = ReadShader(shaders[i].filename);

		// Destroi os shaders caso n�o consiga ler o c�digo
		if (source == NULL) {
			DestroyShaders(shaders);
			return 0;
		}

		// Carrega o c�digo do shader
		glShaderSource(shaders[i].shader, 1, &source, NULL);
		delete[] source;

		// Compila o shader
		glCompileShader(shaders[i].shader);

		// Verifica o estado da compila��o
		GLint compiled;
		glGetShaderiv(shaders[i].shader, GL_COMPILE_STATUS, &compiled);
		// Em caso de erro na compila��o
		if (!compiled) {
			DestroyShaders(shaders);
			return 0;
		}

		// Anexa o shader ao programa
		glAttachShader(program, shaders[i].shader);
	}

	// Linka o programa
	glLinkProgram(program);

	// Verifica o estado do processo de linkagem
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	// Caso d� erro na linkagem
	if (!linked) {
		DestroyShaders(shaders);
		return 0;
	}

	return program;
}

void DestroyShaders(ShaderInfo* shaders) {
	for (int j = 0; shaders[j].type != GL_NONE; j++) {
		// Caso tenha um shader v�lido (i.e., != 0)
		if (shaders[j].shader != 0) glDeleteShader(shaders[j].shader);
		shaders[j].shader = 0;
	}
}