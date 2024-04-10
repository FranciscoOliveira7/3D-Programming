#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace glm;

int main(void) {
	vec3 vertex = vec3(1, 0, 0);

	mat4 Model = mat4(1.0f);

	Model = rotate(Model, radians(45.0f), vec3(0, 0, 1));
	Model = translate(Model, vec3(10, 0, 0));

	for (int i = 0; i < 1; i++) {

		vec4 position = Model * vec4(vertex, 1.0f);

		std::cout << "Coordenadas do Mundo: ";
		std::cout << "\tx=" << position.x <<
			" y=" << position.y <<
			" z=" << position.z;

		std::cout << std::endl;
		std::cout << std::endl;
	}
}