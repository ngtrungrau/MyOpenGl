#pragma once
#include"glfw3.h"
#include<iostream>
#ifdef _DEBUG
#define ASSERT(x) if (!x) __debugbreak();
#define glCall(x) ClearGLError();\
					x;\
				ASSERT(glLogError(#x,__LINE__));
#define ERROR_LOG(x) std::cout<<x<<'\n';\
					__debugbreak();

#else
#define ASSERT(x) 
#define glCall(x) 
#define ERROR_LOG(x)
#endif 
inline void ClearGLError()
{
	while (glGetError() != GL_NO_ERROR);
}
inline bool glLogError(const char* function,unsigned int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[Open Gl Error!!] (" << error << ")"<<"   "<< function << '(' << line << ')' << '\n';
		return false;
	}
	return true;

}
