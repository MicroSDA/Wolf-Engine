#version 440
/*#include "file.glsl"*/

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TextureCoords;
layout (location = 2) in vec3 Normal;

layout (location = 0) out vec2 out_TextureCoords;
layout (location = 1) out vec3 out_Normal;
layout (location = 2) out vec3 out_ToCameraDirection;

layout (location = 3) uniform mat4 ModelM;
layout (location = 4) uniform mat4 ViewM;
layout (location = 5) uniform mat4 ProjectionM;

layout (location = 6) uniform vec3 CameraPosition;
/*uniform mat4 ViewM;
uniform mat4 ProjectionM;*/

//out vec2 texCoordFrag;
//out vec3 normalFrag;

void main()
{
    vec4 MVP = ProjectionM * ViewM * ModelM * vec4(Position, 1.0f);
    gl_Position = MVP;

    //vec3 m_CameraPosition = -inverse(mat3(ViewM)) * ViewM[3].xyz; // Will tweak with - or + !
   /* mat4 mat = inverse(mat4(ViewM));
    vec3 m_CameraPosition = mat[3].xyz;*/ // Will tweak with - or + !

    out_Normal = (ModelM * vec4(normalize(Normal), 0.0)).xyz;
    out_TextureCoords = TextureCoords;
	out_ToCameraDirection  = normalize(CameraPosition - (ModelM * vec4(Position, 1.0f)).xyz);
}