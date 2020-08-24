#version 440
/*#include "file.glsl"*/

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TextureCoords;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 Tangent;

layout (location = 0) out vec2 out_TextureCoords;
layout (location = 1) out vec3 out_Normal;
layout (location = 2) out vec3 out_ToCameraDirection;
layout (location = 3) out vec3 out_Position;
//layout (location = 3) out mat3 out_TBN;
out mat3 out_TBN;


layout (location = 3) uniform mat4 ModelM;
layout (location = 4) uniform mat4 ViewM;
layout (location = 5) uniform mat4 ProjectionM;
layout (location = 6) uniform vec3 CameraPosition;


void main()
{
    vec4 MVP = ProjectionM * ViewM * ModelM * vec4(Position, 1.0f);
    gl_Position = MVP;

    //Попробовать или другоую модель или переводить все в тангентс спейс
     vec3 T = normalize(vec3(ModelM * vec4(Tangent,   0.0)));
     vec3 N = normalize(vec3(ModelM * vec4(Normal,    0.0)));
     T = normalize(T - dot(T, N) * N);
     vec3 B = normalize(cross(T, N));
     if (dot(cross(N, T), B) > 0.0)// если больше или на спине выпукло или на животе 
             T = T * -1.0;
    

	 out_TBN = mat3(T, B, N);

    out_Normal = (ModelM * vec4(normalize(Normal), 0.0)).xyz;
    out_TextureCoords = TextureCoords;
    out_Position = (ModelM * vec4(Position, 1.0f)).xyz;
    out_ToCameraDirection  = normalize(CameraPosition - out_Position);
}