#include"glew.h"
#include "glfw3.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include "Debug.h"

namespace MyGl
{
	Shader::Shader(const std::string& path)
	{
		ShaderProgramSource src = ReadShader(path);
		m_id = CreateShader(src.VertexShader, src.FragmentShader);
	}
	Shader::~Shader()
	{
		glCall(glDeleteProgram(m_id));
	}
	ShaderProgramSource Shader::ReadShader(const std::string& path)
	{
		std::ifstream stream(path);
		std::string line;
		std::stringstream ss[2];
		ShaderType Type = ShaderType::None;
		while (std::getline(stream,line))
		{
			if (line.find("#shader")!=std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)Type = ShaderType::Vertex;
				if (line.find("fragment") != std::string::npos)Type = ShaderType::Fragment;
			}
			else
			{
				if (Type != ShaderType::None)
				{
					ss[static_cast<int>(Type)] << line << '\n';
				}
			}
			
		}
		return { ss[0].str(),ss[1].str()};
	}
	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		glCall(unsigned int id = glCreateShader(type));
		const char* src = source.c_str();
		glCall(glShaderSource(id, 1, &src, nullptr));
		glCall(glCompileShader(id));

		int result;
		glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int length;
			glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			std::string mess;
			mess.resize(length);
			glCall(glGetShaderInfoLog(id, length, &length, mess.data()));

			std::cout << "[Shader Error] Lỗi biên dịch "
				<< (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
				<< " Shader!" << std::endl;
			std::cout << mess << std::endl;

			glCall(glDeleteShader(id));
			return 0;
		}
		return id;
	}
	unsigned int Shader::CreateShader(const std::string& VertexSource, const std::string& FragmentShader)
	{
		glCall(unsigned int Program = glCreateProgram());
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexSource);
		unsigned int vf = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);
		if (!vs || !vf) return 0;
		glCall(glAttachShader(Program, vs));
		glCall(glAttachShader(Program, vf));
		glCall(glLinkProgram(Program));
		glCall(glValidateProgram(Program));
		glCall(glDeleteShader(vs));
		glCall(glDeleteShader(vf));
		return Program;
	}
	void Shader::Bind() const
	{
		glCall(glUseProgram(m_id));
	}
	void Shader::UnBind() const
	{
		glCall(glUseProgram(0));
	}
}