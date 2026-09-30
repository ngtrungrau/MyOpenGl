#include"glew.h"
#include "glfw3.h"
#include"VertexBuffer.h"
#include"Vertex.h"
#include "IndexBuffer.h"
#include "Vao.h"
#include "LayoutBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include<iostream>
using namespace MyGl;
int main()
{
    GLFWwindow* window;


    if (!glfwInit())
        return -1;


    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Glew initialization failed!" << std::endl;
        return -1;
    }

    Vertex vertices[4] = {
        // Top-Left (Trên - Trái)
        { {-0.5f,  0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },

        // Bottom-Left (Dưới - Trái)
        { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },

        // Bottom-Right (Dưới - Phải)
        { { 0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },

        // Top-Right (Trên - Phải)
        { { 0.5f,  0.5f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f} }
    };

    // Danh sách Index để ghép 4 đỉnh thành 2 tam giác (tạo thành hình vuông)
    unsigned int indices[6] = {
        0, 1, 2,  // Tam giác thứ nhất (Top-Left -> Bottom-Left -> Bottom-Right)
        2, 3, 0   // Tam giác thứ hai (Bottom-Right -> Top-Right -> Top-Left)
    };
    
    VertexBuffer vbo(vertices,sizeof(vertices));
    IndexBuffer ibo(indices, 6);
    LayoutBuffer layout;
    layout.AddLayout(GL_FLOAT, 4, GL_FALSE);
    layout.AddLayout(GL_FLOAT, 4, GL_FALSE);
    layout.AddLayout(GL_FLOAT, 2, GL_FALSE);
    Vao vao;
    vao.AddData(vbo, ibo, layout);
    Shader shader("res/shader/Shader.shader");
    Renderer renderer;
    renderer.EnableBlend();
    renderer.SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        renderer.Draw(vao, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}