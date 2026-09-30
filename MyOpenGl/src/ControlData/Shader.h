#pragma once
#include <string>

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
	public:
		Shader(const std::string& path);
		~Shader();
		ShaderProgramSource ReadShader(const std::string& path);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& VertexSource,const std::string& FragmentShader);
		void Bind()const;
		void UnBind() const;



	};
}
