#pragma once
#include <Core/Engine/Render/Light/Light.h>
//TODO : Environment parent
namespace we {
	
	class GeneralLight :public we::Light
	{
	public:
		GeneralLight();
		virtual ~GeneralLight();
		inline void SetDirection(const float& x, const float& y, const float& z) { m_Direction = glm::vec3(x,y,z); }
		inline void SetDirection(const glm::vec3& direction)                     { m_Direction = direction; }

		void Process(const we::Shader& shader);
	private:
		glm::vec3 m_Direction;
	
	};
}

