#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec2 ioTexCoords;

void main()
{
	ioTexCoords = aTexCoords;
	vec4 finalPosition = (uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPos, 1));//PVM * pos
	gl_Position = finalPosition;
}