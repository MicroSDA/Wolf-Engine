#pragma once
#include <Core/Engine/Render/Light/Light.h>

namespace we {
	class PointLight : public we::Light
	{
	public:
		PointLight(int id);
		~PointLight();
		inline void SetPosition(const float& x, const float& y, const float& z) { m_Position = glm::vec3(x, y, z); }
		inline void SetPosition(const   glm::vec3& position)                    { m_Position = position; }
		inline glm::vec3 GetPosition()                                          { return m_Position; }

		inline void SetConstant(const float& constant)                          { m_Constant = constant; }
		inline void SetLinear(const float& linear)                              { m_Linear = linear; }
		inline void SetQaudratic(const float& qaudratic)                        { m_Qaudratic = qaudratic; }

		inline float GetConstant(const float& constant)                         { return m_Constant; }
		inline float GetLinear(const float& linear)                             { return  m_Linear; }
		inline float GetQaudratic(const float& qaudratic)                       { return m_Qaudratic; }

		void Process(const we::Shader& shader) override;
	protected:
		glm::vec3 m_Position;
		float     m_Constant;
		float     m_Linear;
		float     m_Qaudratic;
		int       m_Id;
	private:
		
	};
}



