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
	int Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) !=m_UniformLocationCache.end())
		{
			return m_UniformLocationCache[name];
		}
		int location = -1;
		glCall(location = glGetUniformLocation(m_id, name.c_str()));

		if (location == -1)
			std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

		m_UniformLocationCache[name] = location;
		return location;
		
	}
	void Shader::SetUniform1i(const std::string& name, int value)
	{
		glCall(glUniform1i(GetUniformLocation(name), value));
	}

	void Shader::SetUniform1f(const std::string& name, float value)
	{
		glCall(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		glCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
	}

	void Shader::SetUniform3f(const std::string& name, const Vec3& v)
	{
		glCall(glUniform3f(GetUniformLocation(name), v.x, v.y, v.z));
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	}

	void Shader::SetUniform4f(const std::string& name, const Vec4& v)
	{
		glCall(glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w));
	}

	void Shader::SetUniform4Mat(const std::string& name, const Mat4& mat4)
	{
		// Tự động lấy địa chỉ phần tử float đầu tiên của struct Mat4
		glCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat4.Columns[0].x));
	}

	// ==========================================
	// GET UNIFORMS (Return Trực Tiếp - Chuẩn C++)
	// ==========================================

	int Shader::GetUniform1i(const std::string& name)
	{
		int value = 0;
		glCall(glGetUniformiv(m_id, GetUniformLocation(name), &value));
		return value;
	}

	float Shader::GetUniform1f(const std::string& name)
	{
		float value = 0.0f;
		glCall(glGetUniformfv(m_id, GetUniformLocation(name), &value));
		return value;
	}

	Vec3 Shader::GetUniform3f(const std::string& name)
	{
		Vec3 result;
		glCall(glGetUniformfv(m_id, GetUniformLocation(name), &result.x));
		return result;
	}

	Vec4 Shader::GetUniform4f(const std::string& name)
	{
		Vec4 result;
		glCall(glGetUniformfv(m_id, GetUniformLocation(name), &result.x));
		return result;
	}

	Mat4 Shader::GetUniform4Mat(const std::string& name)
	{
		Mat4 result;
		glCall(glGetUniformfv(m_id, GetUniformLocation(name), &result.Columns[0].x));
		return result;
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