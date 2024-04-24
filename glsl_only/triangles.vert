#version 440 core

out vec3 color;

void main()
{
	const vec2 vertex[6] = {
		vec2(-0.90f, -0.90f ), 
		vec2( 0.85f, -0.90f ), 
		vec2(-0.90f,  0.85f ),

		vec2( 0.90f, -0.85f ), 
		vec2( 0.90f,  0.90f ), 
		vec2(-0.85f,  0.90f )
	};

	gl_Position = vec4(vertex[gl_VertexID], 1.0f, 1.0f);
	color = vec3(1.0f, 0.0f, 0.0f);
}
