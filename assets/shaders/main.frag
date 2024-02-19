#version 460 core

out vec4 FragColor;
in vec3 ioNormal;
in vec3 ioFragPos;

uniform float uAmbientIntense;
uniform vec3 uLightingPosition;

void main()
{
   vec3 normal = normalize(ioNormal);
   vec3 lightDir = normalize(uLightingPosition - ioFragPos);
   float diff = max(dot(normal, lightDir), 0.0);
   if (diff < 0.2)
   diff = 0.2;
   vec3 rgb = diff * uAmbientIntense * vec3(1.0, 1.0, 0.0);
   FragColor = vec4(rgb, 1.0);
}