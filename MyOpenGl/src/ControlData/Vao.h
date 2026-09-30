#pragma once


namespace MyGl
{
	class VertexBuffer;
	class IndexBuffer;
	class LayoutBuffer;
	class Vao
	{
	private:
		unsigned int m_id;
		unsigned int m_count;

	public:
		Vao();
		~Vao();
		void Bind() const;
		void UnBind() const;
		void AddData(const VertexBuffer& vbo, const IndexBuffer& ibo, const LayoutBuffer& layouts);
		unsigned int GetIndexCount()const;

	};
}
