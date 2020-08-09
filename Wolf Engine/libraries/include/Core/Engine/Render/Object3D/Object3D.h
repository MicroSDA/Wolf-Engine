#pragma once
#include <Core/Engine/Render/Drawable.h>
#include <Core/Engine/Render/Model3D/Model3D.h>
#include <Core/Engine/Render/Shader/Shader.h>


class ResourceManager;
namespace we {

	class Object3D : public Drawable
	{
	public:
		Object3D();
		Object3D(const we::Model3D* model, std::vector<Object3D*>& m_pOrigin, unsigned int index);
        virtual ~Object3D();

		void Draw(we::Camera& camera);
		void SetPossition(const float& x, const float& y, const float& z);
		void SetPossition(const glm::vec3& possition);
		void SetRotation(const float& x, const float& y, const float& z);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const float& x, const float& y, const float& z);
		void SetScale(const glm::vec3& scale);
		glm::vec3 GetPossition();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();

		unsigned int m_Index = 0;
		std::vector<Object3D*>* m_pOrigin;
		void SetModel3D(const we::Model3D* model);
	private:
		const we::Model3D* m_pModel3D;
		we::Transform m_Transform;
	};
}