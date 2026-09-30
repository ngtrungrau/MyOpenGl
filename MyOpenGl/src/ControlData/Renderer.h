#pragma once

namespace MyGl
{
	class Vao;
	class Shader;
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		void Clear();
		void Draw(const Vao& vao,const Shader& Shader);
		void EnableBlend() const;
		void DisableBlend() const;
		void SetBlendFunc(unsigned int src, unsigned int dst) const;
		void SetBlendEquation(unsigned int mode) const;

		// --- DEPTH TEST STATE ---
		void EnableDepthTest() const;
		void DisableDepthTest() const;
	};
}
