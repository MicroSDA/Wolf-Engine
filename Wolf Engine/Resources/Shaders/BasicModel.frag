#version 440

layout (location = 0) in vec2 texCoordFrag;
layout (location = 1) in vec3 normalFrag;

layout(binding = 0) uniform sampler2D DIFFUSE_TEXTURE;
layout(binding = 1) uniform sampler2D SPECULAR_TEXTURE;
layout(binding = 2) uniform sampler2D NORMAL_MAP;
/*in vec2 texCoordFrag;
in vec3 normalFrag;*/

//uniform sampler2D DIFFUSE_TEXURE;

void main()
{
	vec4 LightColor = vec4(0.2, 0.8, 0.9, 1.0);
	float light = clamp(dot(vec3(0, 0.5, -0.5), normalFrag),0.0,1.0);
    //gl_FragColor = texture2D(NORMAL_MAP, texCoordFrag.xy) * light;
    gl_FragColor = LightColor * light;

}