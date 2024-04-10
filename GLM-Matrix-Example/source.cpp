// Tipos de dados:
// vec3, vec4, ivec4, mat4, entre outros.
#include <glm/glm.hpp>
// Funções de matrizes de transformação:
// translate, rotate, scale, frustum, perspective, ortho, entre outras.
#include <glm/gtc/matrix_transform.hpp>
// Funções que manipulam a interação entre apontadores e tipos de vetores e matrizes:
// value_ptr
#include <glm/gtc/type_ptr.hpp>

// C++
#include <iostream>

int main(void)
{
	// Resolução da janela da aplicação: 800x600
	int width = 800, height = 600;
	// Vértices que formam o triângulo
	glm::vec3 vertex[] = {
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f)
	};

	// *****************************************************************************************************
	// Matriz de Projeção
	//
	// Funções:
	// glm::mat4 glm::frustum(left, right, bottom, top, near, far);
	// glm::mat4 glm::perspective(fovy, aspect, near, far);
	// glm::mat4 glm::ortho(left, right, bottom, top, zNear, zFar);
	//
	// Nota que em todas estas funções a câmara está na posição (0, 0, 0). É a posição da câmara em OpenGL.
	// Quando movemos a câmara, na realidade estamos a mover o mundo. A posição da câmara não altera.
	// *****************************************************************************************************

	// Frustum: left=-2.0, right=2.0, bottom=-1.5, top=1.5, near=5, far=20
	// left e right	- Especificam coordenadas para os limites esquerdo e direito do plano de projeção.
	// bottom e top	- Especificam coordenadas para os limites inferior e topo do plano de projeção.
	// near e far	- Especificam distâncias entre o Viewer e o Near Clipping Plane e Far Clipping Plane.
	//				  Assim, near e far têm de ser sempre positivos, i.e. > 0.
	glm::mat4 Projection = glm::frustum(-2.0f, 2.0f, -1.5f, 1.5f, 5.0f, 20.0f);

	// Perspetiva: 45° Field of View, 4:3 Aspect Ratio (800/600), Display Range : 5 unidades <-> 20 unidades
	// fovy		- Especifica o ângulo do Field of View na direção de y. Valor em radianos.
	// aspect	- Especifica a relação de aspeto (Aspect Ratio) que determina o campo de visão na direção x.
	//			  O Aspect Ratio é a relação entre largura e altura, i.e., largura/altura.
	// near		- Especifica a distância entre o viewer e o Near Clipping Plane (é sempre positivo, i.e. > 0).
	// far		- Especifica a distância entre o viewer e o Far Clipping Plane (é sempre positivo, i.e. > 0).
	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 5.0f, 20.0f);

	// Ortogonal: left=-2.0, right=2.0, bottom=-1.5, top=1.5, zNear=5, zFar=20
	// Todos os parâmetros correspondem a coordenadas do mundo.
	// Assim, zNear e zFar pode contemplar valores negativos.
	// Note, contudo, que o eixo dos z está invertido.
	// left e right	- Especificam coordenadas para os limites esquerdo e direito do plano de projeção.
	// bottom e top	- Especificam coordenadas para os limites inferior e topo do plano de projeção.
	// zNear e zFar	- Especificam coordenadas para os limites near e far do plano de projeção. (Note que eixo dos z está invertido).
	//				  zNear admite valor 0 e valores negativos.
	//glm::mat4 Projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 5.0f, 20.0f);

	// *****************************************************************************************************
	// Matriz de Visualização (Câmara)
	//
	// Funções:
	// glm::mat4 glm::lookAt(eye, center, up);
	//
	// Nota que na realidade estamos a mover o mundo em direção contrária à posição eye.
	// Em OpenGL a câmara está sempre na posição (0, 0, 0).
	// *****************************************************************************************************

	// eye		- vec3 com posição da câmara nas coordenadas do mundo.
	// center	- vec3 com posição para o local (nas coordenadas do mundo) onde a câmara está a olhar.
	//			  Pode ser definida como a posição + a direção da câmara.
	//			  O vetor (0, 0, -1) indicaria que a câmara está apontada para a direção do z negativo.
	// up		- vec3 com vetor normalizado que indica a orientação da câmara (o seu topo).
	//			  Tipicamente tem valor (0, 1, 0). O vetor (0, -1, 0) colocaria a câmara de "pernas para o ar".
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 0),		// eye
		glm::vec3(0, 0, -1),	// center
		glm::vec3(0, 1, 0)		// head up
	);

	// *****************************************************************************************************
	// Matriz de Modelação (Colocar objeto no mundo)
	//
	// Funções:
	// glm::mat4 glm::translate(glm::mat4 m, glm::vec3 v);
	// glm::mat4 glm::rotate(m, angle, axis);
	// glm::mat4 glm::scale(m, s);
	// *****************************************************************************************************

	// glm::mat4 glm::translate(glm::mat4 m, glm::vec3 v);
	// Gera uma matriz de rotação 4x4, criada pela aplicação à matriz de entrada (m), de uma translação definida pelo vetor translation.
	// m	- Matriz de entrada (Matriz identidade ou outra), onde será aplicada a translação.
	// v	- Vetor de translação, com indicação dos deslocamentos em x, y e z.

	// glm::mat4 glm::rotate(m, angle, axis);
	// Gera uma matriz de rotação 4x4, criada pela aplicação à matriz de entrada (m), de uma rotação de angle radianos, em torno do eixo definido pelo vetor axis.
	// m		- Matriz de entrada, onde será aplicada a rotação.
	// angle	- Ângulo de rotação (em radianos).
	// axis		- Eixo de rotação (recomenda-se que esteja normalizado).

	// glm::mat4glm::scale(m, v);
	// Gera uma matriz de escala 4x4, criada pela aplicação à matriz de entrada (m), de uma alteração de escala definida por um vetor de 3 elementos (s).
	// m	- Matriz de entrada, onde será aplicada a alteração de escala.
	// s	- Rácio de escala para cada eixo.

	// Matriz de Modelação: Matriz Identidade (o modelo inicia na origem)
	glm::mat4 Model = glm::mat4(1.0f);
	// Translação de 10 unidades no eixos dos z negativo
	Model = glm::translate(Model, glm::vec3(0.0f, 0.0f, -10.0f));

	// *****************************************************************************************************
	// Matriz de Modelação, Visualização, Projeção
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
		// Clipping (NOTA: Em Opengl este passo é realizado automaticamente.)
		// *****************************************************************************************************
		if ((position.x > fabs(position.w)) || (position.y > fabs(position.w)) || (position.z > fabs(position.w))) {
			std::cout << "Clipping do Vertex " << i << ":\n";
			std::cout << "\t Vertice fora do cubo canónico.\n\n";
			continue;
		}

		// *****************************************************************************************************
		// Calcular e imprimir cordenadas normalizadas (NOTA: Em OpenGL este passo é realizado automaticamente.)
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
		// Calcular e imprimir cordenadas da tela (NOTA: Em OpenGL este passo é realizado por glViewport.)
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