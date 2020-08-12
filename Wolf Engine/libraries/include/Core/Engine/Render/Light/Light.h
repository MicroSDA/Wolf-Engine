#pragma once
#include <Utilites/Math/glm/glm.hpp>
#include <Core/Engine/Render/Shader/Shader.h>

namespace we {

	class Light
	{
	public:
		Light();
		virtual ~Light();

		inline void SetAmbientColor(const  float& r, const float& g, const float& b) { m_AmbientColor = glm::vec3(r, g, b); }
		inline void SetDiffuseColor(const  float& r, const float& g, const float& b) { m_DiffuseColor = glm::vec3(r, g, b); }
		inline void SetSpecularColor(const float& r, const float& g, const float& b) { m_SpecularColor = glm::vec3(r, g, b); }

		inline void SetAmbientColor(const   glm::vec3& color) { m_AmbientColor = color; }
		inline void SetDiffuseColor(const   glm::vec3& color) { m_DiffuseColor = color; }
		inline void SetSpecularColor(const  glm::vec3& color) { m_SpecularColor = color; }
		inline void SetSpecularIntens(const float& value) { m_SpecularIntens = value; }
		inline glm::vec3 GetAmbientColor() { return m_AmbientColor; }
		inline glm::vec3 GetDiffuseColor() { return m_DiffuseColor; }
		inline glm::vec3 GetSpecularColor() { return m_SpecularColor; }
		inline float GetSetSpecularIntens() { return m_SpecularIntens; }

		virtual void Process(const we::Shader& shader) = 0 ;
	protected:
		glm::vec3 m_AmbientColor;
		glm::vec3 m_DiffuseColor;
		glm::vec3 m_SpecularColor;
		float     m_SpecularIntens;
	};
}


