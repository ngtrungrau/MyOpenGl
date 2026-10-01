#pragma once
#include <string>
#include"Maths.h"
#include<unordered_map>
namespace MyGl
{
	struct ShaderProgramSource
	{
		std::string VertexShader;
		std::string FragmentShader;
	};
	enum class ShaderType : int
	{
		Vertex = 0,
		Fragment = 1,
		None = -1
	};

	class Shader
	{
	private:
		unsigned int m_id;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	public:
		
		Shader(const std::string& path);
		~Shader();
		int GetUniformLocation(const std::string& name);
		// --- SET UNIFORMS ---
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniform3f(const std::string& name, const Vec3& v);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniform4f(const std::string& name, const Vec4& v);
		void SetUniform4Mat(const std::string& name, const Mat4& mat4);

		// --- GET UNIFORMS (Trả về giá trị trực tiếp - Không cần biến hứng) ---
		int   GetUniform1i(const std::string& name);
		float GetUniform1f(const std::string& name);
		Vec3  GetUniform3f(const std::string& name);
		Vec4  GetUniform4f(const std::string& name);
		Mat4  GetUniform4Mat(const std::string& name);

		inline unsigned int GetID() const { return m_id; }
		ShaderProgramSource ReadShader(const std::string& path);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& VertexSource,const std::string& FragmentShader);
		void Bind()const;
		void UnBind() const;



	};
}
