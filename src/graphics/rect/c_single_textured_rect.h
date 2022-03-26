#pragma once
#include "../c_vertex_buffer.h"
#include "../c_index_buffer.h"
#include "../c_vertex_array.h"
#include "../c_vertex_buffer_layout.h"
#include "../c_texture.h"
#include "../c_shader.h"
#include "../c_texture_uniform.h"
#include "../c_mat4_uniform.h"
#include "../../math/glm/ext/matrix_clip_space.hpp"
#include "../c_window.h"

namespace owd_lib
{
	class c_single_textured_rect : public c_basic_object
	{
	public:
		c_single_textured_rect();
		void init(std::shared_ptr<c_shader>& shader, std::shared_ptr<c_texture>& texture);
		void draw();

	private:
		c_window* m_window = c_window::get_instance();

		std::shared_ptr<c_shader> m_shader{};

		std::shared_ptr<c_texture> m_texture{};

		c_texture_uniform m_texture_uniform{};

		c_mat4_uniform m_mat4_uniform{};

		glm::mat4 m_projection = glm::ortho_(m_window->aspect_ratio());

		c_vertex_buffer			m_vertex_buffer{};
		c_index_buffer			m_index_buffer {};
		c_vertex_array			m_vertex_array {};
		
		c_vertex_buffer_layout	m_vertex_buffer_layout{};

		float m_x{ -0.5f };
		float m_y{ 0.0f };

		float m_w{ 0.5f };
		float m_h{ 0.1f };

		vertices_t vertices()
		{
			return
			{
			m_x + -m_w / 2.0f, m_y + -m_h / 2.0f,    0.0f, 0.0f,
			m_x +  m_w / 2.0f, m_y + -m_h / 2.0f,    1.0f, 0.0f,
			m_x +  m_w / 2.0f, m_y +  m_h / 2.0f,    1.0f, 1.0f,
			m_x + -m_w / 2.0f, m_y +  m_h / 2.0f,    0.0f, 1.0f
			};
		}
	};
}