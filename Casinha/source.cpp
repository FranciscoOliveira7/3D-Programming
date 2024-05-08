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

#define NumVAOs 1
#define NumBuffers 2 // Vértices, Cores
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;

int main(void)
{
    GLFWwindow* window;

    glfwSetErrorCallback(print_error);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Casinha", NULL, NULL);
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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        display();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void init(void) {
    GLfloat vertices[NumVertices][2 /*xy*/] = {
        { -0.90f, -0.90f }, { 0.85f, -0.90f }, { -0.90f,  0.85f }, // Triângulo 1
        {  0.90f, -0.85f }, { 0.90f,  0.90f }, { -0.85f,  0.90f }  // Triângulo 2
    };

    GLfloat cores[NumVertices][3 /*rgb*/] = {
        { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, // Triângulo 1
        { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }  // Triângulo 2
    };

    // VAO
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[0]);

    // VBOs
    glGenBuffers(NumBuffers, Buffers);
    for (int i = 0; i < NumBuffers; i++) {

        glBindBuffer(GL_ARRAY_BUFFER, Buffers[i]);
        if (i == 0)
            glBufferStorage(Buffers[i], sizeof(vertices) /*2 * 6 * sizeof(float)*/, vertices, 0);
        else
            glBufferStorage(Buffers[i], sizeof(cores) /*3 * 6 * sizeof(float)*/, cores, 0);
    }


    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER,   "triangles.vert" },
        { GL_FRAGMENT_SHADER, "triangles.frag" },
        { GL_NONE, NULL }
    };

    GLuint program = LoadShaders(shaders);  
    if (!program) exit(EXIT_FAILURE);
    glUseProgram(program);


    // Ligar os atributos aos shaders

    // Obtém a localização do atributo 'vPosition' no 'programa'.
    GLint coordsId = glGetProgramResourceLocation(program, GL_PROGRAM_INPUT, "vPosition");
    GLint coresId = glGetProgramResourceLocation(program, GL_PROGRAM_INPUT, "vColors");

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
    glVertexAttribPointer(coordsId, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glVertexAttribPointer(coresId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(coordsId);
    glEnableVertexAttribArray(coresId);
}

void display(void) {
    static const float black[] = {
        0.0f, 0.0f, 0.0f, 0.0f
    };
    
	glClearBufferfv(GL_COLOR, 0, black);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void print_error(int error, const char* description) {
    cout << description << endl;
}