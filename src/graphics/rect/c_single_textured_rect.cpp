#include "c_single_textured_rect.h"

namespace owd
{
    c_single_textured_rect::c_single_textured_rect()
    {
		set_name(L"single_textured_rect");
		set_logger_name(L"single_textured_rect_logger");
    }
	void c_single_textured_rect::init(std::shared_ptr<c_shader>& shader, std::shared_ptr<c_texture>& texture)
	{
		m_index_buffer.bind();
		m_index_buffer.set
		({
			0, 1, 2,
			2, 3, 0
			});

		m_shader = shader;
		m_texture = texture;

		m_texture_uniform.set_uniform_name("u_texture");

		m_texture_uniform.init(shader->shader_program_id(), 0);

		m_mat4_uniform.set_uniform_name("u_aspect_ratio_projection_matrix");

		m_mat4_uniform.init(shader->shader_program_id(), m_projection);

		m_vertex_buffer_layout.add_element(2);
		m_vertex_buffer_layout.add_element(2);

		m_vertex_buffer.set(vertices());

		m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
    }
	void c_single_textured_rect::draw()
	{
		//-------------------DRAW_TEXTURED_RECT------------------------
		{
			GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

			// 1. ---- BINDING ----.
			{
				m_vertex_array.bind();
				m_vertex_buffer.bind();
				m_index_buffer.bind();
				m_shader->bind();
				m_texture->bind();

				//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
				//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
			}
			//    ---- BINDING ----.

			// 2. ---- DRAW ----
			{
				GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			}
			//    ---- DRAW ----
		}
		//-------------------DRAW_TEXTURED_RECT------------------------
	}
}

