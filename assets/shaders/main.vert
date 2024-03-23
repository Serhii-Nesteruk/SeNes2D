#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 uCameraPos;

out vec3 ioNormal;
out vec3 ioFragPos;
out vec3 ioSurfaceToCamera;

void main()
{
    ioFragPos = vec3(model * vec4(aPos, 1.f));
    ioSurfaceToCamera = uCameraPos - ioFragPos;
    ioNormal = vec3(model * vec4(aNormal, 1.f));
    gl_Position = projection * view * model * vec4(aPos, 1.f);
}