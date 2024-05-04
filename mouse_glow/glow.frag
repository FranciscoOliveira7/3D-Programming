#version 440 core

layout (location = 0) out vec4 fColor; // Cor final do fragmento

layout (location = 1) uniform float screen;

layout (location = 2) uniform vec2 mousePos;

void main(void) {

	fColor = vec4(1-(distance(mousePos, gl_FragCoord.xy) / screen * 3));
}