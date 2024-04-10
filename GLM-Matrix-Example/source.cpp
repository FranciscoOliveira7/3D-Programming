// Tipos de dados:
// vec3, vec4, ivec4, mat4, entre outros.
#include <glm/glm.hpp>
// Fun��es de matrizes de transforma��o:
// translate, rotate, scale, frustum, perspective, ortho, entre outras.
#include <glm/gtc/matrix_transform.hpp>
// Fun��es que manipulam a intera��o entre apontadores e tipos de vetores e matrizes:
// value_ptr
#include <glm/gtc/type_ptr.hpp>

// C++
#include <iostream>

int main(void)
{
	// Resolu��o da janela da aplica��o: 800x600
	int width = 800, height = 600;
	// V�rtices que formam o tri�ngulo
	glm::vec3 vertex[] = {
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f)
	};

	// *****************************************************************************************************
	// Matriz de Proje��o
	//
	// Fun��es:
	// glm::mat4 glm::frustum(left, right, bottom, top, near, far);
	// glm::mat4 glm::perspective(fovy, aspect, near, far);
	// glm::mat4 glm::ortho(left, right, bottom, top, zNear, zFar);
	//
	// Nota que em todas estas fun��es a c�mara est� na posi��o (0, 0, 0). � a posi��o da c�mara em OpenGL.
	// Quando movemos a c�mara, na realidade estamos a mover o mundo. A posi��o da c�mara n�o altera.
	// *****************************************************************************************************

	// Frustum: left=-2.0, right=2.0, bottom=-1.5, top=1.5, near=5, far=20
	// left e right	- Especificam coordenadas para os limites esquerdo e direito do plano de proje��o.
	// bottom e top	- Especificam coordenadas para os limites inferior e topo do plano de proje��o.
	// near e far	- Especificam dist�ncias entre o Viewer e o Near Clipping Plane e Far Clipping Plane.
	//				  Assim, near e far t�m de ser sempre positivos, i.e. > 0.
	glm::mat4 Projection = glm::frustum(-2.0f, 2.0f, -1.5f, 1.5f, 5.0f, 20.0f);

	// Perspetiva: 45� Field of View, 4:3 Aspect Ratio (800/600), Display Range : 5 unidades <-> 20 unidades
	// fovy		- Especifica o �ngulo do Field of View na dire��o de y. Valor em radianos.
	// aspect	- Especifica a rela��o de aspeto (Aspect Ratio) que determina o campo de vis�o na dire��o x.
	//			  O Aspect Ratio � a rela��o entre largura e altura, i.e., largura/altura.
	// near		- Especifica a dist�ncia entre o viewer e o Near Clipping Plane (� sempre positivo, i.e. > 0).
	// far		- Especifica a dist�ncia entre o viewer e o Far Clipping Plane (� sempre positivo, i.e. > 0).
	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 5.0f, 20.0f);

	// Ortogonal: left=-2.0, right=2.0, bottom=-1.5, top=1.5, zNear=5, zFar=20
	// Todos os par�metros correspondem a coordenadas do mundo.
	// Assim, zNear e zFar pode contemplar valores negativos.
	// Note, contudo, que o eixo dos z est� invertido.
	// left e right	- Especificam coordenadas para os limites esquerdo e direito do plano de proje��o.
	// bottom e top	- Especificam coordenadas para os limites inferior e topo do plano de proje��o.
	// zNear e zFar	- Especificam coordenadas para os limites near e far do plano de proje��o. (Note que eixo dos z est� invertido).
	//				  zNear admite valor 0 e valores negativos.
	//glm::mat4 Projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 5.0f, 20.0f);

	// *****************************************************************************************************
	// Matriz de Visualiza��o (C�mara)
	//
	// Fun��es:
	// glm::mat4 glm::lookAt(eye, center, up);
	//
	// Nota que na realidade estamos a mover o mundo em dire��o contr�ria � posi��o eye.
	// Em OpenGL a c�mara est� sempre na posi��o (0, 0, 0).
	// *****************************************************************************************************

	// eye		- vec3 com posi��o da c�mara nas coordenadas do mundo.
	// center	- vec3 com posi��o para o local (nas coordenadas do mundo) onde a c�mara est� a olhar.
	//			  Pode ser definida como a posi��o + a dire��o da c�mara.
	//			  O vetor (0, 0, -1) indicaria que a c�mara est� apontada para a dire��o do z negativo.
	// up		- vec3 com vetor normalizado que indica a orienta��o da c�mara (o seu topo).
	//			  Tipicamente tem valor (0, 1, 0). O vetor (0, -1, 0) colocaria a c�mara de "pernas para o ar".
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 0),		// eye
		glm::vec3(0, 0, -1),	// center
		glm::vec3(0, 1, 0)		// head up
	);

	// *****************************************************************************************************
	// Matriz de Modela��o (Colocar objeto no mundo)
	//
	// Fun��es:
	// glm::mat4 glm::translate(glm::mat4 m, glm::vec3 v);
	// glm::mat4 glm::rotate(m, angle, axis);
	// glm::mat4 glm::scale(m, s);
	// *****************************************************************************************************

	// glm::mat4 glm::translate(glm::mat4 m, glm::vec3 v);
	// Gera uma matriz de rota��o 4x4, criada pela aplica��o � matriz de entrada (m), de uma transla��o definida pelo vetor translation.
	// m	- Matriz de entrada (Matriz identidade ou outra), onde ser� aplicada a transla��o.
	// v	- Vetor de transla��o, com indica��o dos deslocamentos em x, y e z.

	// glm::mat4 glm::rotate(m, angle, axis);
	// Gera uma matriz de rota��o 4x4, criada pela aplica��o � matriz de entrada (m), de uma rota��o de angle radianos, em torno do eixo definido pelo vetor axis.
	// m		- Matriz de entrada, onde ser� aplicada a rota��o.
	// angle	- �ngulo de rota��o (em radianos).
	// axis		- Eixo de rota��o (recomenda-se que esteja normalizado).

	// glm::mat4glm::scale(m, v);
	// Gera uma matriz de escala 4x4, criada pela aplica��o � matriz de entrada (m), de uma altera��o de escala definida por um vetor de 3 elementos (s).
	// m	- Matriz de entrada, onde ser� aplicada a altera��o de escala.
	// s	- R�cio de escala para cada eixo.

	// Matriz de Modela��o: Matriz Identidade (o modelo inicia na origem)
	glm::mat4 Model = glm::mat4(1.0f);
	// Transla��o de 10 unidades no eixos dos z negativo
	Model = glm::translate(Model, glm::vec3(0.0f, 0.0f, -10.0f));

	// *****************************************************************************************************
	// Matriz de Modela��o, Visualiza��o, Proje��o
	// *****************************************************************************************************
	glm::mat4 MVP = Projection * View * Model;

	for (int i = 0; i < 3; i++) {
		// *****************************************************************************************************
		// Imprimir coordenadas de recorte
		// *****************************************************************************************************

		glm::vec4 position = MVP * glm::vec4((glm::vec3)vertex[i], 1.0f);

		std::cout << "Coordenadas de Recorte do Vertex " << i << ":\n";
		std::cout << "\tXclip=" << position.x <<
			" Yclip=" << position.y <<
			" Zclip=" << position.z <<
			" Wclip=" << position.w << std::endl;

		// *****************************************************************************************************
		// Clipping (NOTA: Em Opengl este passo � realizado automaticamente.)
		// *****************************************************************************************************
		if ((position.x > fabs(position.w)) || (position.y > fabs(position.w)) || (position.z > fabs(position.w))) {
			std::cout << "Clipping do Vertex " << i << ":\n";
			std::cout << "\t Vertice fora do cubo can�nico.\n\n";
			continue;
		}

		// *****************************************************************************************************
		// Calcular e imprimir cordenadas normalizadas (NOTA: Em OpenGL este passo � realizado automaticamente.)
		// *****************************************************************************************************

		glm::vec3 norm;
		norm.x = position.x / position.w;
		norm.y = position.y / position.w;
		norm.z = position.z / position.w;

		std::cout << "Coordenadas Normalizadas do Vertex " << i << ":\n";
		std::cout << "\tx=" << norm.x <<
			" y=" << norm.y <<
			" z=" << norm.z << std::endl;

		// *****************************************************************************************************
		// Calcular e imprimir cordenadas da tela (NOTA: Em OpenGL este passo � realizado por glViewport.)
		// *****************************************************************************************************
		glm::vec2 win;
		win.x = (norm.x + 1.0f) * float(width) / 2.0f + 0 /*Xoffset*/;
		win.y = (norm.y + 1.0f) * float(height) / 2.0f + 0 /*Yoffset*/;

		std::cout << "Coordenadas da Tela do Vertex " << i << ":\n";
		std::cout << "\tx=" << win.x <<
			" y=" << win.y << std::endl << std::endl;
	}

	return 0;
}