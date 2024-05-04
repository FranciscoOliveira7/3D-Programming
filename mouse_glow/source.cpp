#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
using namespace std;

#define GLEW_STATIC
#include <GL\glew.h>

#define GLFW_USE_DWM_SWAP_INTERVAL
#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include "shader_util.h"

#define WIDTH 640
#define HEIGHT 480

void print_error(int error, const char* description);
void init(void);
void display(void);

float mousePos[2] = { 1., 0. };
GLuint program = 0;

void cursorCallBack(GLFWwindow* window, double x, double y) {

    mousePos[0] = x;
    mousePos[1] = HEIGHT - y;
    cout << "Cursor x: " << mousePos[0] << "y: "  << mousePos[1] << endl;
}

int main(void)
{
    GLFWwindow* window;

    glfwSetErrorCallback(print_error);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Mouse Glow", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Inicia o gestor de extensões GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    init();

    glfwSetCursorPosCallback(window, cursorCallBack);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        GLint mousePosId = glGetProgramResourceLocation(program, GL_UNIFORM, "mousePos");
        glProgramUniform2fv(program, mousePosId, 1, mousePos);

        display();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void print_error(int error, const char* description) {
    cout << description << endl;
}

void init(void) {
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "triangles.vert" },
        { GL_FRAGMENT_SHADER, "glow.frag" },
        { GL_NONE, NULL }
    };

    program = LoadShaders(shaders);
    if (!program) exit(EXIT_FAILURE);
    glUseProgram(program);

    float screenSize = sqrtf(HEIGHT * HEIGHT + WIDTH * WIDTH);

    GLint screenSizeId = glGetProgramResourceLocation(program, GL_UNIFORM, "screen");
    glProgramUniform1f(program, screenSizeId, screenSize);
}

void display(void) {
    static const float black[] = {
        0.0f, 0.0f, 0.0f, 0.0f
    };
    
	glClearBufferfv(GL_COLOR, 0, black);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}