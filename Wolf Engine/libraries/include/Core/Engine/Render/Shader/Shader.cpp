#include "Shader.h"
#include <fstream>

we::Shader::Shader() : we::Resource()
{
	std::cout << "Shader(" << this << ")\n";
}

we::Shader::Shader(const std::string& fileName)
{
	std::cout << "Shader(" << this << ")\n";

    m_Program = glCreateProgram();
    m_Shaders[0] = CreateShader(LoadShader("./Resources/Shaders/" + fileName + ".vert"), GL_VERTEX_SHADER);
    m_Shaders[1] = CreateShader(LoadShader("./Resources/Shaders/" + fileName + ".frag"), GL_FRAGMENT_SHADER);
   // m_Shaders[2] = CreateShader(LoadShader("./Resources/Shaders/" + fileName + ".geom"), GL_GEOMETRY_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++) {
        glAttachShader(m_Program, m_Shaders[i]);
    }

	/*glBindAttribLocation(m_Program, 0, "position");
	glBindAttribLocation(m_Program, 1, "texCoords");
	glBindAttribLocation(m_Program, 2, "normal");*/

	glLinkProgram(m_Program);
	CheckShaderError(m_Program, GL_LINK_STATUS, true, "Error: Shader program linkin faild: ");

	glValidateProgram(m_Program);
	CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "Error: Shader program validate faild: ");

	
}

we::Shader::~Shader()
{
	
	glUseProgram(0);
	std::cout << "~Shader(" << this << ")\n";
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glDeleteShader(m_Shaders[i]);
	}
	glDeleteProgram(m_Program);
}

void we::Shader::Bind()
{
	glUseProgram(m_Program);
}

void we::Shader::Unbind()
{
	glUseProgram(0);
}

void we::Shader::Update(const we::Transform& transform, const we::Camera& camera)
{
	glm::mat4 camera_perpective = camera.GetPerpective();
	glm::mat4 view = camera.GetView();
	glm::mat4 transform_u = transform.GetModel();

	/*GLuint transformUnifLoaction       = glGetUniformLocation(m_Program, "ModelM");
	GLuint viewUnifLoaction            = glGetUniformLocation(m_Program, "ViewM");
	GLuint projectionUnifLoaction      = glGetUniformLocation(m_Program, "ProjectionM");*/


	/*std::cout << transformUnifLoaction <<"\n";*/

	glUniformMatrix4fv(3, 1, GL_FALSE, &transform_u[0][0]);
	glUniformMatrix4fv(4, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(5, 1, GL_FALSE, &camera_perpective[0][0]);
	glUniform3fv(6, 1, &camera.GetPosition()[0]);
	//glUniform3f(6,  camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

	/*glUniformMatrix4fv(transformUnifLoaction, 1, GL_FALSE, &transform_u[0][0]);
	glUniformMatrix4fv(viewUnifLoaction, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionUnifLoaction, 1, GL_FALSE, &camera_perpective[0][0]);*/

}

GLuint we::Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0) {
		std::cerr << "Error: Shader creation faild" << std::endl;

	}

	const GLchar* shaderSourceSrtings[1];
	GLint ShaderSourceStringLengths[1];

	shaderSourceSrtings[0] = text.c_str();
	ShaderSourceStringLengths[0] = text.length();


	glShaderSource(shader, 1, shaderSourceSrtings, ShaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation faild: ");
	return shader;
}

std::string we::Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());

	/*const std::regex include("^[ ]*\*[ ]*#[ ]*include[ ]+[\"<](.*)[\">].*");
	std::smatch match;*/

	std::string output;
	std::string line;
	if (file.is_open()) {

		while (file.good()) {
			std::getline(file, line);
			/*if (std::regex_search(line, match, include))
			{
				std::cout << match[1] << "\n";
			}*/

			output.append(line + "\n");
		}

	}
	else {
		std::cerr << "Unable to laod shader:" << fileName << std::endl;
	}

	return output;
}

void we::Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
