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
#include "../c_colour_uniform.h"

namespace owd_lib
{
	class c_single_coloured_rect : public c_basic_object
	{
	public:
		c_single_coloured_rect();

		void init(std::shared_ptr<c_shader>& shader);
		void draw();

		void set(float centre_x, float centre_y, float width, float height);

		void set(float centre_x, float centre_y, float width, float height,
			float red, float green, float blue, float alpha);

		void set_position(float centre_x, float centre_y);

		void set_size(float width, float height);

		void set_colour(float red, float green, float blue, float alpha);

	private:
		c_window* m_window = c_window::get_instance();

		std::shared_ptr<c_shader> m_shader{};

		c_mat4_uniform m_mat4_uniform{};

		c_colour_uniform m_colour_uniform{};

		glm::mat4 m_projection = glm::ortho_(m_window->aspect_ratio());

		c_vertex_buffer			m_vertex_buffer{};
		c_index_buffer			m_index_buffer{};
		c_vertex_array			m_vertex_array{};
		
		c_vertex_buffer_layout	m_vertex_buffer_layout{};

		float m_x{ -0.5f };
		float m_y{ 0.0f };

		float m_w{ 0.5f };
		float m_h{ 0.5f };

		vertices_t vertices()
		{
			return
			{
				m_x + -m_w / 2.0f, m_y + -m_h / 2.0f,
				m_x +  m_w / 2.0f, m_y + -m_h / 2.0f,
				m_x +  m_w / 2.0f, m_y +  m_h / 2.0f,
				m_x + -m_w / 2.0f, m_y +  m_h / 2.0f
			};
		}
		bool m_should_update_vertex_array = false;
		void update_vertex_array();
	};
}