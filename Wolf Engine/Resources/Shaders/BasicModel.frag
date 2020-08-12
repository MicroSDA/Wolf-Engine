#version 440

layout (location = 0) in vec2 TextureCoords;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 ToCameraDirection;
layout (location = 3) in vec3 Position;

layout(binding = 0) uniform sampler2D DIFFUSE_TEXTURE;
layout(binding = 1) uniform sampler2D SPECULAR_TEXTURE;
layout(binding = 2) uniform sampler2D NORMAL_MAP;
layout(binding = 3) uniform sampler2D SH_MAP;

struct GeneralLight {
   vec3  direction;
   vec3  colorAmbient;
   vec3  colorDiffuse;
   vec3  colorSpecular;
   float specularIntensivity;
};
struct PointLight {
   vec3  position;
   vec3  colorAmbient;
   vec3  colorDiffuse;
   vec3  colorSpecular;
   float specularIntensivity;
   float constant;
   float linear;                                                                   
   float qaudratic;    
};
struct Material {
   vec3  colorAmbient;
   vec3  colorDiffuse;
   vec3  colorSpecular;
   float specularPower;
   float transparency;
};

const int MAX_POINT_LIGHTS = 100;
const int MAX_SPOT_LIGHTS  = 100;


uniform Material       material;

uniform GeneralLight   generalL;
uniform PointLight     pointL[MAX_POINT_LIGHTS];   


vec4 ProcessGeneralLight(GeneralLight generalLight, Material material)
{
     
    vec4  m_AmbientColor   = vec4(material.colorAmbient * generalLight.colorAmbient, 1.0)  * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
    vec4  m_DiffuesColor   = vec4(0.0, 0.0, 0.0, 1.0);
    vec4  m_SpecularColor  = vec4(0.0, 0.0, 0.0, 1.0);

    float m_DiffuesShading = dot(Normal, generalLight.direction);

    if(m_DiffuesShading > 0.0)
    {
       m_DiffuesColor   = vec4(material.colorDiffuse * generalLight.colorDiffuse * m_DiffuesShading, 1.0) * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
       vec3  m_Reflect  = normalize(-reflect(generalLight.direction, Normal));
       float m_SpecularShading = dot(ToCameraDirection, m_Reflect);
       if(m_SpecularShading > 0.0)
       {
          m_SpecularShading = pow(m_SpecularShading, material.specularPower);
          m_SpecularColor  = vec4(material.colorSpecular * generalLight.colorSpecular, 1.0) * generalLight.specularIntensivity * m_SpecularShading * texture(SH_MAP, TextureCoords).rgba;// specular intensivity
      }
    }

    return vec4(m_AmbientColor + m_DiffuesColor + m_SpecularColor);// Alpha is hardcoded now
}
vec4 ProcessPointLight(PointLight pointLight, Material material)
{
    vec3  m_LightDirection = pointLight.position - Position;                                           
    float m_Distance = length(m_LightDirection);                                                
    m_LightDirection = normalize(m_LightDirection);                                                                                                                                   

    vec4  m_AmbientColor   = vec4(material.colorAmbient * pointLight.colorAmbient, 1.0)  * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
    vec4  m_DiffuesColor   = vec4(0.0, 0.0, 0.0, 1.0);
    vec4  m_SpecularColor  = vec4(0.0, 0.0, 0.0, 1.0);

    float m_DiffuesShading = dot(Normal, m_LightDirection);

    if(m_DiffuesShading > 0.0)
    {
       m_DiffuesColor   = vec4(material.colorDiffuse * pointLight.colorDiffuse * m_DiffuesShading, 1.0) * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
       vec3  m_Reflect  = normalize(-reflect(m_LightDirection, Normal));
       float m_SpecularShading = dot(ToCameraDirection, m_Reflect);
       if(m_SpecularShading > 0.0)
       {
          //float spec = 1.0 * pow(max(dot(ToCameraDirection, m_Reflect), 0.0), material.specularPower);
          m_SpecularShading = pow(m_SpecularShading, material.specularPower);
          m_SpecularColor  = vec4(material.colorSpecular * pointLight.colorSpecular, 1.0) * pointLight.specularIntensivity * m_SpecularShading * texture(SH_MAP, TextureCoords).rgba;// specular intensivity
      }
    }

    float m_Attenuation =  pointLight.constant + pointLight.linear * m_Distance + pointLight.qaudratic * (m_Distance * m_Distance);                                 
    //float m_Attenuation =  1.0 / (pointLight.constant + pointLight.linear * m_Distance +  pointLight.qaudratic * (m_Distance * m_Distance));                                 
    m_AmbientColor  *=m_Attenuation;
    m_DiffuesColor  *=m_Attenuation;
    m_SpecularColor *=m_Attenuation; 

   
    return vec4(m_AmbientColor + m_DiffuesColor + m_SpecularColor) ;// / m_Attenuation;
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

    //gl_FragColor = ProcessGeneralLight(generalL, material);
    vec4 m_GeneralLight = ProcessGeneralLight(generalL, material);
    //gl_FragColor = ProcessPointLight(pointL[0], material);
    gl_FragColor = m_GeneralLight;
}