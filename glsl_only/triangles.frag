#version 440 core

in vec3 color;

layout (location = 0) out vec4 fColor; // Cor final do fragmento

void main()
{
	fColor = vec4(color, 1.0f);
}
