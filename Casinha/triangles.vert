#version 440 core

void main(void) {

	const vec2 vertex[6] = {
		vec2(-1.0f, -1.0f ),
		vec2( 1.0f, -1.0f ),
		vec2(-1.0f,  1.0f ),

		vec2( 1.0f, -1.0f ),
		vec2( 1.0f,  1.0f ),
		vec2(-1.0f,  1.0f )
	};

	gl_Position = vec4(vertex[gl_VertexID], 1.0f, 1.0f);
}
