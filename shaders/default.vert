#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
layout (location = 2) in vec2 aTexture;

// Output a colour and texture coorindates to be used by the fragment shader
out vec3 colour;
out vec2 texCoord;

// Define a scale for the triangle
uniform float scale;

// Define model, view and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
   gl_Position = projection*view*model*vec4(aPos, 1.0);
   colour = aColour;
   texCoord = aTexture;
}