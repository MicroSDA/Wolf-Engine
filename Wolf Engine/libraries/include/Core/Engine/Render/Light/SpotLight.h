#pragma once
#include <Core/Engine/Render/Light/Light.h>

namespace we {

	class SpotLight : public we::Light
	{
	public:
		SpotLight(int id);
		~SpotLight();

		void Process(const we::Shader& shader);
	private:
		glm::vec3 m_Dirrection;
		glm::vec3 m_Position;
		float     m_Constant;
		float     m_Linear;
		float     m_Qaudratic;
		int       m_Id;
		float     m_MinAngle;
		float     m_MaxAngle;
	};
}

