#include "IndexBuffer.h"
#include "glew.h"
#include "glfw3.h"
#include"Debug.h"
namespace MyGl
{
	IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count):m_count(count)
	{
		glGenBuffers(1, &m_id);
		Bind();
		glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
		UnBind();
	}
	IndexBuffer::~IndexBuffer()
	{
		glCall(glDeleteBuffers(1, &m_id));
		
	}
	void IndexBuffer::Bind() const 
	{
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	}
	void IndexBuffer::UnBind() const
	{
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
	unsigned int IndexBuffer::GetCount() const
	{
		return m_count;
	}
}