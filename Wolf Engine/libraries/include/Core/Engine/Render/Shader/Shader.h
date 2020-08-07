#pragma once

#include <Core/Engine/Resources/Resource.h>
#include <Utilites/GLEW/glew.h>
#include <Core/Engine/Render/Camera/Camera.h>
#include <Core/Engine/Render/Transform/Transform.h>
#include <iostream>
#include <string>

namespace we {

	class Shader : public we::Resource
	{
	public:
		Shader();
		Shader(const std::string& fileName);
		virtual ~Shader();

		void Bind();
		void Update(const we::Transform& transform, const we::Camera& camera);
	protected:

	private:
		GLuint CreateShader(const std::string& text, GLenum shaderType);
		std::string LoadShader(const std::string& fileName);
		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

		static const unsigned int NUM_SHADERS = 2;
		GLuint m_Shaders[NUM_SHADERS];
		GLuint m_Program;
	};
}


