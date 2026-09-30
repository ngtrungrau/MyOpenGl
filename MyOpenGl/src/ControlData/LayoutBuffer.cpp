#include "LayoutBuffer.h"
#include "glew.h"
#include "glfw3.h"
#include<iostream>
#include "Debug.h"
namespace MyGl
{
	LayoutBuffer::LayoutBuffer(): m_stride(0)
	{
	}
	LayoutBuffer::~LayoutBuffer()
	{
	}
	void LayoutBuffer::AddLayout(unsigned int type, unsigned int count, unsigned char normalised)
	{
		ElementLayout tmp = { type,count,normalised };
		m_stride += tmp.GetSize();
		m_elements.push_back(std::move(tmp));
	}
	const std::vector<ElementLayout>& LayoutBuffer::GetElementLayouts() const
	{
		return m_elements;
	}
	const unsigned int& LayoutBuffer::GetStride() const
	{
		return m_stride;
	}
	unsigned int ElementLayout::GetSize()const 
	{
		switch (type)
		{
		case GL_FLOAT:
			return count * sizeof(float);
			break;
		case GL_INT:
			return count * sizeof(int);
			break;
		case GL_UNSIGNED_INT:
			return count * sizeof(unsigned int);
			break;
		case GL_UNSIGNED_BYTE:
			return count * sizeof(unsigned char);
			break;
		case GL_BYTE:
			return count * sizeof(char);
			break;
		default:
			std::cout << "You need to declare more type in LayoutBuffer";
			ASSERT(0);
		}
	}
}


