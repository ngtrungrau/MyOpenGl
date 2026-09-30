#pragma once
namespace MyGl
{
	struct Vertex
	{
		struct {
			float x, y, z, w;
		}position;
		struct 
		{
			float r, g, b, a;
		}color;
		struct 
		{
			float u, v;
		}Mapping;
	};
}