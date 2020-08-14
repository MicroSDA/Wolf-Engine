#pragma once
#include <Utilites/Math/glm/glm.hpp>
#include <Core/Engine/Render/Shader/Shader.h>
namespace we {

	class Material
	{
	public:
		Material();
		virtual ~Material();
		inline void SetAmbientColor(const  float& r, const float& g, const float& b)    { m_AmbientColor  = glm::vec3(r, g, b); }
		inline void SetDiffuseColor(const  float& r, const float& g, const float& b)    { m_DiffuseColor  = glm::vec3(r, g, b); }
		inline void SetSpecularColor(const float& r, const float& g, const float& b)    { m_SpecularColor = glm::vec3(r, g, b); }
		inline void SetShinines(const float& value)                                     { m_Shinines = value; }
		inline void SetTransparentMask(const  float& r, const float& g, const float& b) { m_TransparentMask = glm::vec3(r, g, b); }

		inline void SetTransparentMask(const  glm::vec3& color)                         { m_TransparentMask = color; }
		inline void SetAmbientColor(const  glm::vec3& color)                            { m_AmbientColor  = color; }
		inline void SetDiffuseColor(const  glm::vec3& color)                            { m_DiffuseColor  = color; }
		inline void SetSpecularColor(const glm::vec3& color)                            { m_SpecularColor = color; }

		inline glm::vec3 GetAmbientColor()     { return m_AmbientColor;  }
		inline glm::vec3 GetDiffuseColor()     { return m_DiffuseColor;  }
		inline glm::vec3 GetSpecularColor()    { return m_SpecularColor; }
		inline glm::vec3 GetTransparency()     { return m_TransparentMask; }
		inline float     GetShinines()         { return m_Shinines; }
		
		void Process(we::Shader& shader) const;
	private:
		glm::vec3 m_AmbientColor;
		glm::vec3 m_DiffuseColor;
		glm::vec3 m_SpecularColor;
		glm::vec3 m_TransparentMask;
		float     m_Shinines;
	
		
	};
}