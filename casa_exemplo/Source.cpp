#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
using namespace std;

#define GLEW_STATIC
#include <GL\glew.h>

#define GLFW_USE_DWM_SWAP_INTERVAL
#include <GLFW\glfw3.h>

#include "LoadShaders.h"

void print_gl_info();
void print_error(int error, const char *description);
void init(void);
void display(void);

#define WIDTH 800
#define HEIGHT 600

#define NumVAOs 2 //1
#define NumBuffers 3 // Vértices, Cores, EBO
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 9;
const GLuint NumIndices = 15;

int main(void) {
	GLFWwindow *window;

	glfwSetErrorCallback(print_error);

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL - House", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	
	// Inicia o gestor de extensões GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	print_gl_info();
	init();

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		display();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void print_gl_info() {
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << "\nOpenGL version " << major << '.' << minor << endl;

	const GLubyte *glversion = glGetString(GL_VERSION);
	const GLubyte *glvendor = glGetString(GL_VENDOR);
	const GLubyte *glrenderer = glGetString(GL_RENDERER);
	cout << "\nVersion:  " << glversion << endl << 
		    "Vendor:   " << glvendor << endl << 
		    "Renderer: " << glrenderer << endl;

	cout << "\nSupported GLSL versions:\n";
	const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << "Higher supported version:\n" << glslversion << endl;
	GLint numglslversions;
	cout << "Other supported versions:\n";
	glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &numglslversions);
	for (int n = 0; n < numglslversions; n++) {
		cout << glGetStringi(GL_SHADING_LANGUAGE_VERSION, n) << endl;
	}
}

void print_error(int error, const char *description) {
	cout << description << endl;
}

void init(void) {
	// ****************************************************
	// Criar arrays de dados na RAM
	// ****************************************************

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

	// ****************************************************
	// VAOs - Vertex Array Objects
	// ****************************************************
	
	// Gerar 'NumVAOs' nomes para VAOs.
	// Neste caso, como NumVAOS = 1, gera apenas 1 nome.
	glGenVertexArrays(NumVAOs, VAOs);
	// Faz bind do VAO, cujo nome está definido em 'VAOs[0]', com o contexto do OpenGL.
	// Um VAO é criado no primero bind que lhe seja feito.
	// Este VAO passa a estar ativo até que seja feito o bind a outro VAO, ou seja feito o bind com valor 0.
	glBindVertexArray(VAOs[0]);
	
	// ************************************************************
	// VBOs - Vertex Buffer Objects / EBOs - Element Buffer Objects
	// ************************************************************

	// Gera 'NumBuffers' nomes para VBOs e EBOs.
	// Neste caso, como NumBuffers = 3, gera 3 nomes
	// Esta função pode ser chamada antes da criação de VAOs.
	glGenBuffers(NumBuffers, Buffers);
	// Para cada nome de VBO
	for (int i = 0; i < NumBuffers - 1; i++) {
		// Faz bind do VBO ao buffer GL_ARRAY_BUFFER.
		// GL_ARRAY_BUFFER é utilizado para dados de atributos de vértices.
		// Um VBO é criado no primeiro bind que lhe seja feito.
		// Este VBO passa a estar ativo até que seja feito o bind a outro VBO ou seja feito o bind com valor 0.
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[i]);
		if (i == 0) {
			// Inicializa o VBO (que está ativo) com memória de tamanho imutável.
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices) /*2 * 6 * sizeof(float)*/, vertices, 0);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		}
		else {
			// Inicializa o VBO (que está ativo) com memória de tamanho imutável.
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(cores) /*3 * 6 * sizeof(float)*/, cores, 0);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(cores), vertices, GL_STATIC_DRAW);
		}
	}

	// Para o EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[NumBuffers - 1]);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 0);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ****************************************************
	// Shaders
	// ****************************************************

	ShaderInfo  shaders[] = {
		{ GL_VERTEX_SHADER,   "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint programa = LoadShaders(shaders);
	if (!programa) exit(EXIT_FAILURE);
	glUseProgram(programa);

	// ****************************************************
	// Ligar Atributos aos Shaders
	// ****************************************************

	// As localizações de atributos fazem parte do programa shader, e são completamente independentes do VAO.
	// Podemos, assim, obter as localizações de atributos sem que antes se tenha criado qualquer VAO.
	// ------------------------------------------------------------------------------------------------------
	// Obtém a localização do atributo 'vPosition' no 'programa'.
	//GLint coordsId = glGetAttribLocation(programa, "vPosition"); // Para versões anteriores à 4.3
	GLint coordsId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vPosition"); // Para versões >= 4.3
	// Obtém a localização do atributo 'vColors' no 'programa'.
	//GLint coresId = glGetAttribLocation(programa, "vColors"); // Para versões anteriores à 4.3
	GLint coresId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vColors"); // Para versões >= 4.3
	
	//glBindVertexArray(VAOs[0]); // Não é necessário fazer o bind do VAO, pois ele já é o que está ativo no contexto do OpenGL.

	// Ativa o VBO 'Buffers[0]'.
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	// Liga a localização do atributo 'vPosition' dos shaders do 'programa', ao VBO e VAO (ativos).
	// Especifica também como é que a informação do atributo 'coordsId' deve ser interpretada.
	// Neste caso, o atributo irá receber, por vértice, 2 elementos do tipo float.
	glVertexAttribPointer(coordsId, 2 /*2 elementos por vértice*/, GL_FLOAT/*do tipo float*/, GL_FALSE, 0, nullptr);

	// Ativa o VBO 'Buffers[1]'.
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	// Liga a localização do atributo 'vColors' dos shaders do 'programa', ao VBO e VAO (ativos).
	// Especifica também como é que a informação do atributo 'coordsId' deve ser interpretada.
	// Neste caso, o atributo irá receber, por vértice, 3 elementos do tipo float.
	glVertexAttribPointer(coresId, 3 /*3 elementos por vértice*/, GL_FLOAT/*do tipo float*/, GL_FALSE, 0, nullptr);
	
	// Habitita o atributo com localização 'coresId' para o VAO ativo.
	// Os atributos de um VAO estão desativados por defeito.
	glEnableVertexAttribArray(coordsId);
	// Habitita o atributo com localização 'coresId' para o VAO ativo.
	// Os atributos de um VAO estão desativados por defeito.
	glEnableVertexAttribArray(coresId);
}

void display(void) {
	static const float black[] = {
		0.0f, 0.0f, 0.0f, 0.0f
	};

	/***************************************** Fase 2 ********************************************************/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL/*GL_LINE*//*GL_POINT*/);
	glEnable(GL_LINE_SMOOTH); // Ativa antialiasing (desabilitado por defeito)
	glLineWidth(2.0f); // Define a largura da linha
	//glPointSize(5.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND); // Para que o GL_LINE_SMOOTH tenha efeito, é necessário ativar o GL_BLEND
	/*********************************************************************************************************/

	// A função glClearBufferfv(GL_COLOR, ...) é semelhante à função glClearColor().
	glClearBufferfv(GL_COLOR, 0, black);

	// Vincula (torna ativo) o VAO
	glBindVertexArray(VAOs[0]);

	// Envia comando para desenho de primitivas GL_TRIANGLES, que utilizará os dados do VAO vinculado.
	// A função glDrawElements() vai usar os dados do EBO para desenho.
	//int offset = 3 * sizeof(GLuint); // Offset do element array buffer. Ignora os 3 primeiros índices do EBO.
	//glDrawElements(GL_TRIANGLES, NumIndices-3 /*quero que desenhe apenas 3 vértices*/, GL_UNSIGNED_INT, (void *) offset);
	glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, (void *) 0);
}
