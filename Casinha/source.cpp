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

#define NumVAOs 2
#define NumBuffers 3 // Vértices, Cores, EBO
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 9;
const GLuint NumIndices = 15;

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
    GLfloat vertices[NumVertices][2] = {
        { -0.5f, -0.9f }, { 0.5f, -0.9f }, { -0.5f,  0.1f }, { 0.5f,  0.1f },
        {  0.0f,  0.4f },
        { -0.3f, -0.9f }, { -0.1f, -0.9f }, { -0.3f, -0.5f }, { -0.1f, -0.5f }
    };

    GLfloat cores[NumVertices][3] = {
        { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, // Branco
        { 1.0f, 0.0f, 0.0f }, // Vermelho
        { 0.59f, 0.29f, 0.0f }, { 0.59f, 0.29f, 0.0f }, { 0.59f, 0.29f, 0.0f }, { 0.59f, 0.29f, 0.0f } // Castanho
    };

    GLuint indices[NumIndices] = { 0, 1, 2, 1, 3, 2, // Parede
        2, 3, 4, // Telhado
        5, 6, 7, 6, 8, 7 // Porta
    };

    // VAO
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[0]);

    // VBOs
    glGenBuffers(NumBuffers, Buffers);
    for (int i = 0; i < NumBuffers - 1; i++) {

        glBindBuffer(GL_ARRAY_BUFFER, Buffers[i]);
        if (i == 0)
            glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices) /*2 * 6 * sizeof(float)*/, vertices, 0);
        else if (i == 1)
            glBufferStorage(GL_ARRAY_BUFFER, sizeof(cores) /*3 * 6 * sizeof(float)*/, cores, 0);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[NumBuffers - 1]);
    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 0);


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

    // Vincula (torna ativo) o VAO
    glBindVertexArray(VAOs[0]);

    glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, (void *) 0);
}

void print_error(int error, const char* description) {
    cout << description << endl;
}