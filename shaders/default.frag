#version 330 core

in vec3 colour;
in vec2 texCoord;
in vec3 normal;
in vec3 currentPos;

out vec4 FragColour;

uniform sampler2D tex0;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;

void main() {
    float ambient = 0.2;

    vec3 unitNormal = normalize(normal);
    vec3 lightDirection = normalize(lightPos - currentPos);
    float diffuse = max(dot(unitNormal, lightDirection), 0.0);
    float specularLight = 0.5;
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectDirection = reflect(-lightDirection, unitNormal);
    float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0), 8.0);
    float specular = specularAmount*specularLight;

    FragColour = lightColour*(diffuse + ambient + specular)*texture(tex0, texCoord);
}