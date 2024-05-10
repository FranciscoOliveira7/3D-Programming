#version 440 core

in vec2 vPosition;
in vec3 vColors;

out vec3 color;

void main() {

	gl_Position = vec4(vPosition, 1.0f, 1.0f);
	color = vColors;
}
