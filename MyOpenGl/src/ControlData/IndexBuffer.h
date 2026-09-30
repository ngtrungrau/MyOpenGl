#pragma once
namespace MyGl
{
	class IndexBuffer
	{
	private:
		unsigned int m_id;
		unsigned int m_count;
	public:
		IndexBuffer(unsigned int* indices, unsigned int count);
		~IndexBuffer();
		void Bind() const;
		void UnBind() const;
		unsigned int GetCount() const;
	};
}