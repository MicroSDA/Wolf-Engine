#version 400
/*#include "file.glsl"*/

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 texCoordFrag;
out vec3 normalFrag;

void main()
{
    vec4 MVP = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
    texCoordFrag = texCoords;
	normalFrag = (modelMatrix * vec4(normalize(normal), 0.0)).xyz;
    gl_Position = MVP;
}