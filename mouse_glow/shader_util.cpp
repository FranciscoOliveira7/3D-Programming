#pragma once

#include <iostream>
#include <fstream>

#define GLEW_STATIC
#include <GL\glew.h>

#include "shader_util.h"

static const GLchar* ReadShader(const char* filename) {
	// Abre o ficheiro 'filename' em binário, e coloca-se na última posição do ficheiro.
	std::ifstream file(filename, std::ifstream::ate, std::ifstream::binary);

	if (file.is_open()) {
		std::streampos file_size = file.tellg();

		// Reposiciona a leitura do ficheiro no seu início.
		file.seekg(0, std::ios::beg);

		GLchar* source = new GLchar[int(file_size)];

		file.read(source, file_size);

		// Fecha a string.
		source[file_size] = 0;

		file.close();

		// Retorna o endereço da string alocada.
		return const_cast<const GLchar*>(source);
	}
	else std::cerr << "Error opening the file \"" << filename << "\"" << std::endl;

	return nullptr;
}