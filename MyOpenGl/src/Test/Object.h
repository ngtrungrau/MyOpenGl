#pragma once
#include "Maths.h"
#include "Texture.h"
#include"Shader.h"
#include"Vao.h"
#include"Renderer.h"
#include<iostream>
#include<string>
#include<vector>
#include"LayoutBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
namespace MyGl
{
	class Object {
	private:
		std::string m_name;

		std::unique_ptr<Vao> m_vao;
		std::unique_ptr<Texture> m_texture;
		std::unique_ptr<Shader> m_shader;
		std::weak_ptr<Renderer> weak_Renderer;
		std::unique_ptr<VertexBuffer> m_vbo;
		std::unique_ptr<IndexBuffer> m_ibo;
		///////////////////
		std::string m_shader_path;
		std::string m_texture_path;
		std::string m_vertices_path;
		std::string m_indices_path;

		char tmp_shader_path[128];
		char tmp_texture_path[128];
		char tmp_vertices_path[128];
		char tmp_indices_path[128];
		//////////////////////////

		std::vector<float> m_vertices;
		std::vector<unsigned int>m_indices;
		LayoutBuffer m_layous;

		Mat4 m_model;
		Mat4& shared_camera_view;
		Mat4& proj;
		unsigned int m_texture_slot;
		bool MVP;
		bool last_MVP;
		////////////

		
		
		

	public:
		Object(const std::string& name, unsigned int texture_slot,const std::shared_ptr<Renderer>& shared_renderer, Mat4& camera_view,  Mat4& Proj);
		virtual ~Object();
		virtual void Translate(const Vec3& dir);
		virtual void Render();
		virtual void RenderImGui();


	};
}