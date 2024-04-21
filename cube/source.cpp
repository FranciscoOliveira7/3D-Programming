#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include <vector>

#include <Windows.h>
#include <gl\GL.h>

#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

void init(void);

#define WIDTH 800
#define HEIGHT 600

GLfloat ZOOM = 10.0f;
GLfloat ANGLE = 0.0f;

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	// Se faz zoom in
	if (yoffset == 1) {
		// Incremento no zoom, varia com a distância da câmara
		ZOOM += fabs(ZOOM) * 0.1f;
	}
	// Senão, se faz zoom out
	else if (yoffset == -1) {
		// Incremento no zoom, varia com a distância da câmara
		ZOOM -= fabs(ZOOM) * 0.1f;
	}
	std::cout << "ZOOM = " << ZOOM << std::endl;
}

std::vector<glm::vec3> Load3DModel(void) {
	// 6 faces * 4 vértices por face
	glm::vec3 point[6 * 4] = {
		// Frente
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		// Trás
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		// Direita
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		// Esquerda
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		// Cima
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		// Baixo
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f)
	};

	std::vector<glm::vec3> ret;
	for (auto i : point)
		ret.push_back(i);

	return ret;
}

void display(std::vector<glm::vec3> obj, glm::mat4 mvp) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float* vertex_stream = static_cast<float*>(glm::value_ptr(obj.front()));

	std::vector<glm::vec3> colors{
		glm::vec3(1.0f, 0.0f, 0.0f), // Red
		glm::vec3(1.0f, 1.0f, 0.0f), // Yellow
		glm::vec3(0.0f, 1.0f, 0.0f), // Green
		glm::vec3(0.0f, 1.0f, 1.0f), // Cyan
		glm::vec3(0.0f, 0.0f, 1.0f), // Blue
		glm::vec3(1.0f, 0.0f, 1.0f)  // Magenta
	};

	// Desenha quad em modo imediato
	glBegin(GL_QUADS);
	/* obj.size() * (obj.front().length()) é o mesmo que (6*4)*3 */
	/* 6 faces * 4 vértices por face * 3 coordenadas por vértice */
	for (int nv = 0; nv < 6 * 4 * 3; nv += 3) {
		// Uma cor por face
		glColor3f(colors[nv / (4 * 3)].r, colors[nv / (4 * 3)].g, colors[nv / (4 * 3)].b);
		glm::vec4 vertex = glm::vec4(vertex_stream[nv], vertex_stream[nv + 1], vertex_stream[nv + 2], 1.0f);
		// Cálculo das coordenadas de recorte
		glm::vec4 transformed_vertex = mvp * vertex;
		// Divisão de Perspetiva
		glm::vec4 normalized_vertex = transformed_vertex / transformed_vertex.w;
		// Desenho do vértice
		glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
	}
	glEnd();
}

int main(void) {
	std::vector<glm::vec3> obj = Load3DModel();
	/*for (auto i : model)
		std::cout << "x:" << i.x << " y:" << i.y << " z:" << i.z << std::endl;*/

	GLFWwindow* window;

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "P3D - Trabalho Pratico 1 (Part #1)", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	init();

	glfwSetScrollCallback(window, scrollCallback);

	// Projection
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.f);
	//glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.0f, 20.0f);

	while (!glfwWindowShouldClose(window)) {
		// View
		glm::mat4 view = glm::lookAt(
			glm::vec3(0.0f, 0.0f, ZOOM),	// Posição da câmara no mundo
			glm::vec3(0.0f, 0.0f, -1.0f),	// Direção para a qual a câmara esta apontada
			glm::vec3(0.0f, 1.0f, 0.0f)		// Vector vertical
		);
		// Model
		glm::mat4 model = glm::mat4(1.0f);
		// Vai efetuando uma rotação ao objeto (apenas para podermos ver todas as faces desenhadas).
		model = glm::rotate(model, ANGLE += 0.001f, glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));
		// MVP
		glm::mat4 mvp = projection * view * model;

		display(obj, mvp);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	// Descomentar para ativar o Face Culling
	//glEnable(GL_CULL_FACE);
}
