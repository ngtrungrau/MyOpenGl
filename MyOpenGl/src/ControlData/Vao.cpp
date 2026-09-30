#include "Vao.h"
#include "glew.h"
#include "glfw3.h"
#include "Debug.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "LayoutBuffer.h"
namespace MyGl
{
	Vao::Vao():m_id(0),m_count(0)
	{
		glCall(glGenVertexArrays(1, &m_id));
	
	}
	Vao::~Vao()
	{
		glCall(glDeleteVertexArrays(1, &m_id));
	}
	void Vao::Bind() const 
	{
		glCall(glBindVertexArray(m_id));
		
	}
	void Vao::UnBind() const
	{
		glCall(glBindVertexArray(0));
	}
	void Vao::AddData(const VertexBuffer& vbo, const IndexBuffer& ibo, const LayoutBuffer& layouts)
	{
		m_count = ibo.GetCount();
		Bind();
		vbo.Bind();
		ibo.Bind();
		unsigned int index = 0;
		unsigned int start = 0;
		for (auto it : layouts.GetElementLayouts())
		{
			glCall(glEnableVertexAttribArray(index));
			glCall(glVertexAttribPointer(index, it.count, it.type, it.normalised, layouts.GetStride(), (const void*)(start)));
			++index;
			start += it.GetSize();
		}
		UnBind();
	}
	unsigned int Vao::GetIndexCount() const
	{
		return m_count;
	}
}