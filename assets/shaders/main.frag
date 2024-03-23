#version 460 core

out vec4 FragColor;
in vec3 ioNormal;
in vec3 ioFragPos;
in vec3 ioSurfaceToCamera;

uniform float uAmbientIntense;
uniform vec3 uLightingPosition;

void main()
{
   vec3 normal = normalize(ioNormal);
   vec3 lightDir = normalize(uLightingPosition - ioFragPos);
   float diffuse = max(dot(normal, lightDir), 0.0);
   if (diffuse < 0.2)
      diffuse = 0.2;

   vec3 surfaceToCamera = normalize(ioSurfaceToCamera);
   vec3 halfVector = normalize(surfaceToCamera + lightDir);
   float specular = pow(dot(normal, halfVector), 32);

   vec3 rgb = diffuse * uAmbientIntense * vec3(1.0, 1.0, 0.0);
   FragColor = vec4(rgb, 1.0);
   FragColor.rgb += specular;
}