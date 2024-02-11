#version 460 core

out vec4 FragColor;
uniform float uAmbientIntense;

void main()
{
   vec3 rgb = uAmbientIntense * vec3(1.0, 1.0, 0.0);
   FragColor = vec4(rgb, 1.0);
}