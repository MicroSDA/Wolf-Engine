#pragma once

#include <Core/Engine/Resources/Resource.h>
#include <Utilites/GLEW/glew.h>
#include <Core/Engine/Render/Camera/Camera.h>
#include <Core/Engine/Render/Transform/Transform.h>
#include <iostream>
#include <string>
#include <regex>

namespace we {

	class Shader : public we::Resource
	{
	public:
		Shader();
		Shader(const std::string& fileName);
		virtual ~Shader();

		void Bind();
		static void Unbind();
		void Update(const we::Transform& transform, const we::Camera& camera);
		//inline GLuint& GetProgram() { return m_Program; }
		unsigned int GetProgram() const { return m_Program; }
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


