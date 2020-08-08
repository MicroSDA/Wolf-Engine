#version 400

in vec2 texCoordFrag;
in vec3 normalFrag;

void main()
{
	vec4 LightColor = vec4(0.5, 0.5, 0.5, 0.5);
	
	float light = clamp(dot(vec3(0, 0.5, -0.5), normalFrag),0.0,1.0);
    gl_FragColor = LightColor * light;    
}