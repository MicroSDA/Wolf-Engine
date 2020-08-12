#pragma once
#include <Core/Engine/Render/Light/Light.h>

namespace we {
	class PointLight : public we::Light
	{
	public:
		PointLight();
		~PointLight();
		inline void SetPosition(const float& x, const float& y, const float& z) { m_Position = glm::vec3(x, y, z); }
		inline void SetPosition(const   glm::vec3& position)                    { m_Position = position; }
		inline glm::vec3 GetPosition()                                          { return m_Position; }

		void Process(const we::Shader& shader);
	private:
		glm::vec3 m_Position;
		float     m_Constant;
		float     m_Linear;
		float     m_Qaudratic;
	};
}



