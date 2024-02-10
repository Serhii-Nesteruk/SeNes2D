#version 460 core

out vec4 FragColor;

uniform vec2 uWindowSize;

void main()
{
   vec2 uv = gl_FragCoord.xy / uWindowSize;

   FragColor = vec4(uv, 0.0, 1.0);
}