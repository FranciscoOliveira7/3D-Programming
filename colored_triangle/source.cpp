//#pragma comment(lib, "glfw3.lib")
//#pragma comment(lib, "opengl32.lib")
//
//#include <iostream>
//
//#include <Windows.h>
//#include <gl\GL.h>
//
//#include <GLFW\glfw3.h>
//
//void init(void);
//void display(void);
//
//#define WIDTH 800
//#define HEIGHT 600
//
//int main(void) {
//	GLFWwindow* window;
//
//	if (!glfwInit()) return -1;
//
//	window = glfwCreateWindow(WIDTH, HEIGHT, "GLSL - My1stProject - Modo Imediato", NULL, NULL);
//	if (window == NULL) {
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	init();
//
//	while (!glfwWindowShouldClose(window)) {
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		display();
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//void init(void) {
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//}
//
//void display(void) {
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	// Desenha triangulo em modo imediato
//	glBegin(GL_TRIANGLES);
//	glColor3f(0.0f, 1.0f, 0.0f);
//	glVertex2f(-0.90f, -0.90f);
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glVertex2f(0.85f, -0.90f);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex2f(-0.90f, 0.85f);
//	glEnd();
//}

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
using namespace std;

#include <Windows.h>
#include <gl\GL.h>

#include <GLFW\glfw3.h>

void print_error(int error, const char* description);
void init(void);
void display(void);

#define WIDTH 800
#define HEIGHT 600

int main(void) {
	GLFWwindow* window;

	glfwSetErrorCallback(print_error);

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "GLSL - My1stProject - Vertex Array", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

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

void print_error(int error, const char* description) {
	cout << description << endl;
}

void init(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	const GLint nPoints = 3;
	const GLint nVertexComponents = 2, nColorComponents = 4;
	GLfloat tPoints[nPoints][nVertexComponents] = {
		{ -0.90f, -0.90f },
		{ 0.85f, -0.90f },
		{ -0.90f,  0.85f }
	};
	GLfloat tColors[nPoints][nColorComponents] = {
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
	};

	// Habilita o array de v�rtices para escrita. A fun��o glDrawArrays far� a escrita 
	// dos dados para esse array.

	// glEnableClientState(GL_VERTEX_ARRAY) habilita a transmiss�o de um array de v�rtices 
	// para o pipeline de renderiza��o na placa gr�fica.
	// Por outras palavras, ao se invocar a fun��o glDrawArrays() o pipeline vai consumir 
	// os atributos especificados por glEnableClientState(GL_VERTEX_ARRAY) e cuja origem 
	// dos dados foi definida por glVertexPointer().
	glEnableClientState(GL_VERTEX_ARRAY);
	// glEnableClientState(GL_COLOR_ARRAY) habilita a transmiss�o de um array de cor 
	// para o pipeline de renderiza��o na placa gr�fica.
	// Por outras palavras, ao se invocar a fun��o glDrawArrays() o pipeline vai consumir 
	// os atributos especificados por glEnableClientState(GL_COLOR_ARRAY) e cuja origem 
	// dos dados foi definida por glColorPointer().
	glEnableClientState(GL_COLOR_ARRAY);

	// Especifica a localiza��o (na CPU) e o formato dos dados com as coordenadas de desenho.
	glVertexPointer(nVertexComponents, GL_FLOAT, 0, tPoints);
	// Especifica a localiza��o (na CPU) e o formato dos dados de cor de cada v�rtice.
	glColorPointer(nColorComponents, GL_FLOAT, 0, tColors);
	//glNormalPointer(...);

	// Desenha o tri�ngulo.
	// S�o utilizados 3 elementos de cada array habilitado, para construir a sequ�ncia das 
	// primitivas geom�tricas (neste caso, sequ�ncia de GL_TRIANGLES).
	// Os dados s�o copiados para o GPU.
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Desabilita o uso, pelo pipeline, dos dados dos v�rtices.
	glDisableClientState(GL_VERTEX_ARRAY);
	// Desabilita o uso, pelo pipeline, dos dados de cor.
	glDisableClientState(GL_COLOR_ARRAY);
}