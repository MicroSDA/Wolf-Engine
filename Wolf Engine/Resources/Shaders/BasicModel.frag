#version 440

layout (location = 0) in vec2 TextureCoords;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 ToCameraDirection;

layout(binding = 0) uniform sampler2D DIFFUSE_TEXTURE;
layout(binding = 1) uniform sampler2D SPECULAR_TEXTURE;
layout(binding = 2) uniform sampler2D NORMAL_MAP;

struct GeneralLight {
   vec3 direction;
   vec3 colorAmbient;
   vec3 colorDiffuse;
   vec3 colorSpecular;
};

uniform GeneralLight GeneralL;

vec4 ProcessGeneralLight(GeneralLight generalLight)
{
    
    //TODO: material_reflection at first position
    vec3  m_AmbientColor   = vec3(1, 1, 1)  * texture(DIFFUSE_TEXTURE,  TextureCoords).rgb;
    vec3  m_DiffuesColor   = vec3(0.0f, 0.0f, 0.0f);
    vec3  m_SpecularColor  = vec3(0.0f, 0.0f, 0.0f);

    float m_DiffuesShading = dot(Normal, vec3(0, 0.0, -1.0));

    if(m_DiffuesShading > 0.0f)
    {
       m_DiffuesColor   = vec3(1, 1, 1) * m_DiffuesShading * texture(DIFFUSE_TEXTURE,  TextureCoords).rgb;
       vec3  m_Reflect  = normalize(-reflect(vec3(0, 0.0, -1.0), Normal));
       float m_SpecularShading = dot(ToCameraDirection, m_Reflect);
       if(m_SpecularShading > 0.0f)
       {
          m_SpecularShading = pow(m_SpecularShading, 100);// 0.5 specular_power
          m_SpecularColor  = vec3(1, 1, 1) * 10 * m_SpecularShading * texture(DIFFUSE_TEXTURE, TextureCoords).rgb;// 0.5 specular intensivity
      }
    }

    return vec4(vec3(m_DiffuesColor + m_SpecularColor), 1.0f);// Alpha is hardcoded now
}

void main()
{
	/*vec4 LightColor = vec4(0.2, 0.8, 0.9, 1.0);
	float light = clamp(dot(vec3(0, 0.5, -0.5), Normal),0.0,1.0);
    vec4 Dif =  texture2D(DIFFUSE_TEXTURE, TextureCoords.xy);
    vec4 Spec = texture2D(SPECULAR_TEXTURE, TextureCoords.xy);
    vec4 Norm = texture2D(NORMAL_MAP, TextureCoords.xy);
    gl_FragColor = (Dif * Spec * Norm) * light;*/
    //gl_FragColor = texture2D(SPECULAR_TEXTURE, texCoordFrag.xy) * light;
    //gl_FragColor = LightColor * light;

    gl_FragColor = ProcessGeneralLight(GeneralL);
}