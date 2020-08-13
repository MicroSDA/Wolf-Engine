#pragma once
#include <Core/Engine/Render/Light/PointLight.h>

namespace we {

	class SpotLight : public we::PointLight
	{
	public:
		SpotLight(int id);
		~SpotLight();
		inline void SetDirection(const float& x, const float& y, const float& z) { m_Direction = glm::vec3(x, y, z); }
		inline void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
		inline glm::vec3 GetDirection() { return m_Direction; }

		void Process(const we::Shader& shader);
	private:
		glm::vec3 m_Direction;
		float     m_MinAngle;
		float     m_MaxAngle;
	};
}

