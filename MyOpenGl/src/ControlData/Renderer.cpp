#include "glew.h"
#include "glfw3.h"
#include "Debug.h"
#include"Vao.h"
#include "Renderer.h"
#include"Shader.h"
namespace MyGl
{
	Renderer::Renderer()
	{
	}
	Renderer::~Renderer()
	{
	}
	void Renderer::Clear()
	{
		glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	}
	void Renderer::Draw(const Vao& vao, const Shader& shader)
	{
		vao.Bind();
		shader.Bind();
		glCall(glDrawElements(GL_TRIANGLES, vao.GetIndexCount(), GL_UNSIGNED_INT, (const void*)0));
	}
	void Renderer::EnableBlend() const
	{
		glCall(glEnable(GL_BLEND));
	}
	void Renderer::DisableBlend() const
	{
		glCall(glDisable(GL_BLEND));
	}
	void Renderer::SetBlendFunc(unsigned int src, unsigned int dst) const
	{
		glCall(glBlendFunc(src, dst));
	}
	void Renderer::SetBlendEquation(unsigned int mode) const
	{
		glCall(glBlendEquation(mode));
	}
	void Renderer::EnableDepthTest() const
	{
		glCall(glEnable(GL_DEPTH_TEST));
		glCall(glDepthFunc(GL_LESS));
	}
	void Renderer::DisableDepthTest() const
	{
		glCall(glDisable(GL_DEPTH_TEST));
	}
}