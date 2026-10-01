#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <string>
namespace MyGl {
	class Texture
	{
	private:
		unsigned int m_id;
		unsigned char* m_data;
		int m_width, m_height, m_BPP;
	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const; 
		void UnBind() const;

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }
	};
}