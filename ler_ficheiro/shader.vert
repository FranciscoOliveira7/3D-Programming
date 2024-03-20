#version 440 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColors;
layout(location = 2) in vec2 vTextureCoords;
	
layout(location = 0) out vec3 color;
layout(location = 1) out vec2 textureCoord;

void main()
{
	gl_Position = vec4(vPosition, 1.0f);
	color = vColors;
	textureCoord = vTextureCoords;
}