#include "Object.h"
#include"glew.h"
#include "imgui.h"
#include "LoadData.h"
namespace MyGl
{
	Object::Object(const std::string& name, unsigned int texture_slot, const std::shared_ptr<Renderer>& shared_renderer,
		 Mat4& camera_view,
		 Mat4& Proj) :shared_camera_view(camera_view),
		proj(Proj),
		m_texture_slot(texture_slot),
		m_name(name)
	{
		
		m_model.Identity();
		weak_Renderer = shared_renderer;
		m_shader_path = "res/shader/Shader.shader";
		m_texture_path = "res/image/image.png";
		m_vertices_path = "res/asset/vertices.ver";
		m_indices_path = "res/asset/indices.ind";
		m_vao = std::make_unique<Vao>();
		m_layous.AddLayout(GL_FLOAT, 4, GL_FALSE);
		m_layous.AddLayout(GL_FLOAT, 4, GL_FALSE);
		m_layous.AddLayout(GL_FLOAT, 2, GL_FALSE);
		LoadVertexBuffer(m_vertices_path, m_vertices);
		LoadIndexBuffer(m_indices_path, m_indices);
		m_vbo = std::make_unique<VertexBuffer>(m_vertices.data(), m_vertices.size() * sizeof(float));
		m_ibo = std::make_unique<IndexBuffer>(m_indices.data(), m_indices.size());
		m_vao->AddData(*m_vbo.get(), *m_ibo.get(), m_layous);

		memset(tmp_shader_path, 0, sizeof(tmp_shader_path));
		memset(tmp_texture_path, 0, sizeof(tmp_texture_path));
		strcpy_s(tmp_shader_path, m_shader_path.c_str());
		strcpy_s(tmp_texture_path, m_texture_path.c_str());

		memset(tmp_vertices_path, 0, sizeof(tmp_vertices_path));
		memset(tmp_indices_path, 0, sizeof(tmp_indices_path));
		strcpy_s(tmp_vertices_path, m_vertices_path.c_str());
		strcpy_s(tmp_indices_path, m_indices_path.c_str());


		m_texture = std::make_unique<Texture>(m_texture_path);
		m_texture->Bind(m_texture_slot);
		m_shader = std::make_unique<Shader>(m_shader_path);
		m_shader->Bind();
		m_shader->SetUniform1i("uTexture", m_texture_slot);
		m_shader->UnBind();




	}
	Object::~Object()
	{
	}
	void Object::Translate(const Vec3& dir)
	{
		m_model.Translate(dir);
	}
	void Object::Render()
	{
		
		m_shader.get()->Bind();
		m_shader.get()->SetUniform4Mat("u_MVP", proj * shared_camera_view * m_model);
		if (auto render = weak_Renderer.lock())
		{
			
			render->Draw(*m_vao.get(), *m_shader.get());
		}
	}
	void Object::RenderImGui()
	{
		ImGui::Text(m_name.c_str());
		ImGui::InputText("Shader_path", tmp_shader_path,sizeof(tmp_shader_path));
		ImGui::SameLine();
		if (ImGui::Button("Conform##shader"))
		{
			m_shader_path = tmp_shader_path;
			m_shader = std::make_unique<Shader>(m_shader_path);
			m_shader.get()->Bind();
			m_shader.get()->SetUniform1i("uTexture", m_texture_slot);
			m_shader.get()->UnBind();
		}
		ImGui::InputText("Texture_path", tmp_texture_path, sizeof(tmp_texture_path));
		ImGui::SameLine();
		if (ImGui::Button("Conform##Texture"))
		{
			m_texture_path = tmp_texture_path;
			m_texture = std::make_unique<Texture>(m_texture_path);
			m_texture.get()->Bind(m_texture_slot);
		}


		ImGui::InputText("Vertices_path", tmp_vertices_path, sizeof(tmp_vertices_path));
		ImGui::SameLine();
		if (ImGui::Button("Conform##Vertices"))
		{
			m_vertices_path = tmp_vertices_path;
			LoadVertexBuffer(m_vertices_path, m_vertices);
		}
		ImGui::InputText("Indices_path", tmp_indices_path, sizeof(tmp_indices_path));
		ImGui::SameLine();
		if (ImGui::Button("Conform##Indices"))
		{
			m_indices_path = tmp_indices_path;
			LoadIndexBuffer(m_indices_path, m_indices);
		}
		if (ImGui::Button("Conform_VAO"))
		{
			m_vao->AddData(*m_vbo.get(), *m_ibo.get(), m_layous);
		}



		




	}
}