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
   float shininesStrength;
};
struct PointLight {
   vec3  position;
   vec3  colorAmbient;
   vec3  colorDiffuse;
   vec3  colorSpecular;
   float shininesStrength;
   float constant;
   float linear;                                                                   
   float qaudratic;    
};
struct SpotLight {
   vec3  direction;
   vec3  position;
   vec3  colorAmbient;
   vec3  colorDiffuse;
   vec3  colorSpecular;
   float shininesStrength;
   float constant;
   float linear;                                                                   
   float qaudratic; 
   float minAngle;
   float maxAngle;
};
struct Material {
   vec3  colorAmbient;
   vec3  colorDiffuse;
   vec3  colorSpecular;
   float shinines;
   float transparency;
};

const int MAX_POINT_LIGHTS = 100;
const int MAX_SPOT_LIGHTS  = 100;

uniform Material       material;

uniform GeneralLight   generalL;
uniform PointLight     pointL[MAX_POINT_LIGHTS];   
uniform SpotLight      spotL[MAX_SPOT_LIGHTS];   


uniform int POINT_LIGHTS_COUNT;
uniform int SPOT_LIGHTS_COUNT;

vec4 ProcessGeneralLight(GeneralLight generalLight, Material material)
{
    vec4  m_AmbientColor   = vec4(material.colorAmbient * generalLight.colorAmbient, 1.0)  * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
    vec4  m_DiffuesColor   = vec4(0.0, 0.0, 0.0, 1.0);
    vec4  m_SpecularColor  = vec4(0.0, 0.0, 0.0, 1.0);

    float m_DiffuesShading = dot(Normal, -generalLight.direction);

    if(m_DiffuesShading > 0.0)
    {
       m_DiffuesColor   = vec4(material.colorDiffuse * generalLight.colorDiffuse * m_DiffuesShading, 1.0) * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
      //vec3  m_Reflect  = normalize(reflect(-generalLight.direction, Normal));
       //float m_SpecularShading = dot(ToCameraDirection, m_Reflect);
       float m_SpecularShading = dot(Normal, normalize(-generalLight.direction + ToCameraDirection));
       if(m_SpecularShading > 0.0)
       {
          m_SpecularShading = pow(m_SpecularShading, material.shinines);
          m_SpecularColor  = vec4(material.colorSpecular * generalLight.colorSpecular, 1.0) * generalLight.shininesStrength * m_SpecularShading * 
          (texture(SPECULAR_TEXTURE, TextureCoords).rgba * texture(SPECULAR_TEXTURE, TextureCoords).a); // specular based on alpha ?
      }
    }

    return vec4(m_AmbientColor + m_DiffuesColor + m_SpecularColor);// Alpha is hardcoded now
}
vec4 ProcessPointLight(PointLight pointLight, Material material)
{
    vec3  m_LightDirection = normalize(pointLight.position - Position);                                           
    float m_Distance = length(m_LightDirection);                                                
    //m_LightDirection = normalize(m_LightDirection);                                                                                                                                   

    vec4  m_AmbientColor   = vec4(material.colorAmbient * pointLight.colorAmbient, 1.0)  * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
    vec4  m_DiffuesColor   = vec4(0.0, 0.0, 0.0, 1.0);
    vec4  m_SpecularColor  = vec4(0.0, 0.0, 0.0, 1.0);

    float m_DiffuesShading = dot(Normal, m_LightDirection);

    if(m_DiffuesShading > 0.0)
    {
       m_DiffuesColor   = vec4(material.colorDiffuse * pointLight.colorDiffuse * m_DiffuesShading, 1.0) * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
       //vec3  m_Reflect  = normalize(-reflect(m_LightDirection, Normal));
       //float m_SpecularShading = dot(ToCameraDirection, m_Reflect);
       float m_SpecularShading = dot(Normal, normalize(m_LightDirection + ToCameraDirection));
      
       if(m_SpecularShading > 0.0)
       {
          //float spec = 1.0 * pow(max(dot(ToCameraDirection, m_Reflect), 0.0), material.specularPower);
          m_SpecularShading = pow(m_SpecularShading, material.shinines);
          m_SpecularColor  = vec4(material.colorSpecular * pointLight.colorSpecular, 1.0) * pointLight.shininesStrength * m_SpecularShading *
          (texture(SPECULAR_TEXTURE, TextureCoords).rgba * texture(SPECULAR_TEXTURE, TextureCoords).a); // specular based on alpha ?
      }
    }

                           
    float m_Attenuation =  1.0 / (pointLight.constant + pointLight.linear * m_Distance +  pointLight.qaudratic * (m_Distance * m_Distance));                                 
    m_AmbientColor  *=m_Attenuation;
    m_DiffuesColor  *=m_Attenuation;
    m_SpecularColor *=m_Attenuation; 

   
    return vec4(m_AmbientColor + m_DiffuesColor + m_SpecularColor);
}
vec4 ProcessSpotLight(SpotLight spotLight, Material material)                                         
{                                          
    
    vec3  m_LightDirection = normalize(spotLight.position - Position);                             
    float m_SpotFactor = dot(m_LightDirection,  normalize(-spotLight.direction)); //spotLight.direction                                  
                                                                                            
    if (m_SpotFactor > spotLight.minAngle)
    { 
        float m_Epsilon   = spotLight.minAngle - spotLight.maxAngle;
        m_SpotFactor = smoothstep(0.0, 1.0, (m_SpotFactor - spotLight.minAngle) / m_Epsilon);
        float m_Distance  = length(m_LightDirection); 
        vec4  m_AmbientColor   = vec4(material.colorAmbient * spotLight.colorAmbient, 1.0)  * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
        vec4  m_DiffuesColor   = vec4(0.0, 0.0, 0.0, 1.0);
        vec4  m_SpecularColor  = vec4(0.0, 0.0, 0.0, 1.0);

        float m_DiffuesShading = dot(Normal, m_LightDirection);

        if(m_DiffuesShading > 0.0)
        {
           m_DiffuesColor   = vec4(material.colorDiffuse * spotLight.colorDiffuse * m_DiffuesShading, 1.0) * texture(DIFFUSE_TEXTURE,  TextureCoords).rgba;
           //vec3  m_Reflect  = normalize(-reflect(m_LightDirection, Normal));
           //float m_SpecularShading = dot(ToCameraDirection, m_Reflect);
           float m_SpecularShading = dot(Normal, normalize(m_LightDirection + ToCameraDirection));
           if(m_SpecularShading > 0.0)
           {
              //float spec = 1.0 * pow(max(dot(ToCameraDirection, m_Reflect), 0.0), material.specularPower);
              m_SpecularShading = pow(m_SpecularShading, material.shinines);
              m_SpecularColor  = vec4(material.colorSpecular * spotLight.colorSpecular, 1.0) * spotLight.shininesStrength * m_SpecularShading *
              (texture(SPECULAR_TEXTURE, TextureCoords).rgba * texture(SPECULAR_TEXTURE, TextureCoords).a); // specular based on alpha ?
          }
        }

         float m_Attenuation =  1.0 / (spotLight.constant + spotLight.linear * m_Distance +  spotLight.qaudratic * (m_Distance * m_Distance));
         m_DiffuesColor  *=m_SpotFactor;
         m_SpecularColor *=m_SpotFactor;

         m_AmbientColor  *=m_Attenuation;
         m_DiffuesColor  *=m_Attenuation;
         m_SpecularColor *=m_Attenuation;

        return vec4(m_AmbientColor + m_DiffuesColor + m_SpecularColor); 

    }else{

        return vec4(0,0,0,0);  
     
    }
}  
void main()
{

    vec4 m_TotalColor = ProcessGeneralLight(generalL, material);

    for(int i = 0; i < POINT_LIGHTS_COUNT; i++)
    {
        m_TotalColor += ProcessPointLight(pointL[i], material);
    }
    for(int i = 0; i < SPOT_LIGHTS_COUNT; i++)
    {
        m_TotalColor += ProcessSpotLight(spotL[i], material);
    }

    //m_TotalColor.rgb = pow(m_TotalColor.rgb, vec3(1.0/1.2));

    gl_FragColor = m_TotalColor;
}