#pragma once
#include <vector>
namespace MyGl
{
	struct ElementLayout
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalised;
		unsigned int GetSize()const;

	};
	class LayoutBuffer
	{
	private:
		std::vector<ElementLayout> m_elements;
		unsigned int m_stride = 0;
	public:
		LayoutBuffer();
		~LayoutBuffer();
		void AddLayout(unsigned int type, unsigned int count, unsigned char normalised);
		const std::vector<ElementLayout>& GetElementLayouts() const;
		const unsigned int& GetStride() const;
	};
}
