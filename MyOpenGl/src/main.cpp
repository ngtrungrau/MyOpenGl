#include"glew.h"
#include "glfw3.h"
#include"VertexBuffer.h"
#include"Vertex.h"
#include "IndexBuffer.h"
#include "Vao.h"
#include "LayoutBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Maths.h"
#include<iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Object.h"
using namespace MyGl;
int main()
{
    GLFWwindow* window;


    if (!glfwInit())
        return -1;


    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
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

    ///////////////////////////////////////////////////////////////////////
    // IMGUI SETUPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP!!!!!!!!!!!!!!!!!!!!!!!
    // ==========================================
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsClassic();

    const char* glsl_version = "#version 330"; // Hoặc #version 130 tùy bản OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    // ==========================================
    //////////////////////////////////////////////////////////////////////////////

   
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>();

    //renderer.get()->EnableBlend();
    //renderer.get()->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    renderer.get()->EnableDepthTest();

    Mat4 Model;
    Model.Identity();
    Mat4 Camera;
    Camera.Identity();
    Mat4 Proj;
    Proj.Identity();
    float tmp[3] = { 4,4,0 };
    Proj.Perspective(10, 10, 10);
    float z=0.0001f;
    Object fivestar("bruh",0,renderer,Camera,Proj);
    while (!glfwWindowShouldClose(window))
    {
        // IMGUI SETUPPPPPPPPPPPPPPP!!!!!!
        glfwPollEvents();
        // Thông báo cho ImGui tính toán delta time, input bàn phím/chuột của frame này
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ==========================================
        //////////////////////////////////////////////////////////////// 
        renderer.get()->Clear();
        fivestar.Render();
        fivestar.RenderImGui();

        ImGui::Begin("test");
        ImGui::SliderFloat3("Perspective", tmp, 0.0f, 100.0f);
        ImGui::DragFloat("Z", &z,0.00001f,-0.001f,0.001f);
        Vec3 dir(0,0,z);
        fivestar.Translate(dir);
        Proj.Perspective(tmp[0], tmp[1], tmp[2]);
        ImGui::End();





        ImGui::Render();

        // Thực sự vẽ ImGui đè lên trên Scene OpenGL vừa vẽ ở Bước 2
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}