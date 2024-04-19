#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Windows.h>
#include <gl\GL.h>

#include <GLFW\glfw3.h>


using namespace glm;

void init(void);
void display(GLfloat&);

#define WIDTH 800
#define HEIGHT 600

int main(void) {
	GLFWwindow* window;

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "GLSL - My1stProject - Modo Imediato", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	init();

	GLfloat angle = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		display(angle);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void init(void) {
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void display(GLfloat &angle) {
	// Desenha triangulo em modo imediato
	glBegin(GL_TRIANGLES);
	vec3 verteces[6 * 4] = {
		// Frente
		vec3(-1.0f, -1.0f,  1.0f),
		vec3(1.0f, -1.0f,  1.0f),
		vec3(1.0f,  1.0f,  1.0f),
		vec3(-1.0f,  1.0f,  1.0f),
		// Trás
		vec3(-1.0f, -1.0f, -1.0f),
		vec3(-1.0f,  1.0f, -1.0f),
		vec3(1.0f,  1.0f, -1.0f),
		vec3(1.0f, -1.0f, -1.0f),
		// Direita
		vec3(1.0f, -1.0f,  1.0f),
		vec3(1.0f, -1.0f, -1.0f),
		vec3(1.0f,  1.0f, -1.0f),
		vec3(1.0f,  1.0f,  1.0f),
		// Esquerda
		vec3(-1.0f, -1.0f,  1.0f),
		vec3(-1.0f,  1.0f,  1.0f),
		vec3(-1.0f,  1.0f, -1.0f),
		vec3(-1.0f, -1.0f, -1.0f),
		// Cima
		vec3(-1.0f,  1.0f,  1.0f),
		vec3(1.0f,  1.0f,  1.0f),
		vec3(1.0f,  1.0f, -1.0f),
		vec3(-1.0f,  1.0f, -1.0f),
		// Baixo
		vec3(-1.0f, -1.0f,  1.0f),
		vec3(-1.0f, -1.0f, -1.0f),
		vec3(1.0f, -1.0f, -1.0f),
		vec3(1.0f, -1.0f,  1.0f)
	};

	mat4 Projection = perspective(radians(45.0f), (float)WIDTH / HEIGHT, 5.0f, 20.0f);

	mat4 View = lookAt(
		vec3(0, 0, 10),
		vec3(0, 0, 0),
		vec3(0, 1, 0)
	);

	mat4 Model = mat4(1.0f);

	Model = rotate(Model, angle += 0.0005f, normalize(vec3(1.0f, 1.0f, 0.0f)));

	mat4 MVP = Projection * View * Model;

	bool idk = 0;

	for (int i = 0; i < 6 * 4; i++) {
		if (idk) glColor3f(0.0f, 0.0f, 1.0f);
		else glColor3f(1.0f, 0.0f, 0.0f);
		idk = !idk;

		vec4 vertex = vec4(verteces[i].x, verteces[i].y, verteces[i].z, 1.0f);
		vec4 trans_vertex = MVP * vertex;
		vec4 normalized_vertex = trans_vertex / trans_vertex.w;
		glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
	}
	glEnd();
}