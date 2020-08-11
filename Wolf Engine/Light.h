#pragma once
#include <Utilites/Math/glm/glm.hpp>
#include <Core/Engine/Render/Shader/Shader.h>
//TODO : Environment parent
namespace we {
	class Light
	{
	public:
		Light();
		virtual ~Light();
		inline void SetDirection(const float& x, const float& y, const float& z) { m_Direction = glm::vec3(x,y,z); }
		inline void SetDirection(const glm::vec3& direction)                     { m_Direction = direction; }

		inline void SetAmbientColor(const  float& r, const float& g, const float& b)     { m_AmbientColor = glm::vec3(r, g, b); }
		inline void SetDiffuseColor(const  float& r, const float& g, const float& b)     { m_DiffuseColor = glm::vec3(r, g, b); }
		inline void SetSpecularColor(const float& r, const float& g, const float& b)     { m_SpecularColor = glm::vec3(r, g, b); }
	
		inline void SetAmbientColor(const  glm::vec3& color) { m_AmbientColor = color; }
		inline void SetDiffuseColor(const  glm::vec3& color) { m_DiffuseColor = color; }
		inline void SetSpecularColor(const glm::vec3& color) { m_SpecularColor = color; }

		inline glm::vec3 GetDirection()        { return m_Direction; }
		inline glm::vec3 GetAmbientColor()     { return m_AmbientColor; }
		inline glm::vec3 GetDiffuseColor()     { return m_DiffuseColor; }
		inline glm::vec3 GetSpecularColor()    { return m_SpecularColor; }
		
		void Process(const we::Shader& shader);
	private:
		glm::vec3 m_Direction;
		glm::vec3 m_AmbientColor;
		glm::vec3 m_DiffuseColor;
		glm::vec3 m_SpecularColor;
	};
}

