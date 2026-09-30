#pragma once
namespace MyGl
{
	class VertexBuffer
	{
	private:
		unsigned int m_id;
	public:
		VertexBuffer(const void* data,unsigned int size);
		~VertexBuffer();
		void Bind() const;
		void UnBind() const;

	};
}