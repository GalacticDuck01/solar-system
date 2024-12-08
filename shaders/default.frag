#version 330 core

in vec3 colour;
in vec2 texCoord;

out vec4 FragColour;

uniform sampler2D tex0;

void main() {
    FragColour = texture(tex0, texCoord);
}