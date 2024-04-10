#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace glm;

int main(void) {
	vec3 vertex[] = {
		vec3(0.5, -0.5, 0.0),
		vec3(0.0, 0.5, 0.0),
		vec3(-0.5, -0.5, 0.0)
	};

	mat4 Projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);

	mat4 View = lookAt(
		vec3(0, 0, 0),
		vec3(0, 0, -1),
		vec3(0, 1, 0)
	);

	mat4 Model = mat4(1.0f);

	mat4 MVP = Projection * View * Model;

	for (int i = 0; i < 3; i++) {

		vec3 position = MVP * vec4(vertex[i], 1.0f);

		std::cout << "\n\nCoordenadas do Mundo: \n";
		std::cout << "\tx=" << position.x <<
			" y=" << position.y <<
			" z=" << position.z;
	}
}