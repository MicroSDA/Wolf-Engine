#version 400

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 texCoordFrag;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
	texCoordFrag = texCoord;
	
}