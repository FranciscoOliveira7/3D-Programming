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

#define HEIGHT 600
#define WIDTH 800

using namespace glm;

std::vector<vec3> LoadModel(void);
void Draw(mat4, std::vector<vec3>);

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "3D Square", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

	std::vector<vec3> cube = LoadModel();
	float zoom = 10.0f, rotation = 0.0f;

	mat4 projection = perspective(radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window))
	{
		mat4 model = mat4(1.0f);
		model = rotate(model, rotation += 0.005f, vec3(1, 1, 0));
		mat4 view = lookAt(
			vec3(0, 0, zoom),
			vec3(0, 0, -1),
			vec3(0, 1, 0)
		);

		mat4 mvp = projection * view * model;

		Draw(mvp, cube);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void Draw(mat4 mvp, std::vector<vec3> model) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec3 colors[] = {
		vec3(1, 0, 0), // red
		vec3(0, 0, 1), // blue
		vec3(1, 1, 0), // yellow
		vec3(0, 1, 0), // green
		vec3(0, 1, 1), // cyan
		vec3(1, 0, 1)  // magenta
	};

	glBegin(GL_QUADS);
	
	for (int i = 0; i < 6 * 4; i++) {
		glColor3f(colors[i / 4].r, colors[i / 4].g, colors[i / 4].b);
		vec4 vertex = vec4(model[i].x, model[i].y, model[i].z, 1.0f);
		vec4 transformed_vertex = mvp * vertex;
		vec4 normalized_vertex = transformed_vertex / transformed_vertex.w;

		// Silly Vertex warping idk
		//normalized_vertex.x = trunc(normalized_vertex.x * 100) / 100;
		//normalized_vertex.y = trunc(normalized_vertex.y * 100) / 100;
		//normalized_vertex.z = trunc(normalized_vertex.z * 100) / 100;

		glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
	}

	glEnd();
}

std::vector<vec3> LoadModel(void) {
	// 6 faces * 4 vértices por face
	vec3 point[6 * 4] = {
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

	std::vector<vec3> ret;
	for (auto i : point) ret.push_back(i);

	return ret;
}