#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColour;
layout (location = 3) in vec2 aTexture;

// Outputs that go to the fragment shader
out vec3 currentPos;
out vec3 normal;
out vec3 colour;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;

void main() {
   currentPos = vec3(model*vec4(aPos, 1.0));
   normal = aNormal;
   colour = aColour;
   texCoord = aTexture;

   gl_Position = camMatrix*vec4(currentPos, 1.0);
}