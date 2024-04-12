#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <windows.h>
extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

int main(void) {
	GLFWwindow* window;

	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
	window = glfwCreateWindow(1280, 720, "My 1st P3D Project", nullptr, nullptr);
	//window = glfwCreateWindow(800, 600, "My 1st P3D Project", glfwGetPrimaryMonitor(), nullptr); // Full screen
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	bool color = 0;

	while (!glfwWindowShouldClose(window)) {
		if (color) glClearColor(1, 0, 0, 1);
		else glClearColor(0, 0, 1, 1);
		color = !color;

		glClear(GL_COLOR_BUFFER_BIT);
		//glfwSwapBuffers(window);
		glFinish();

		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}