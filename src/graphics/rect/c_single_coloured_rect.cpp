#include "c_single_coloured_rect.h"

namespace owd_lib
{
    c_single_coloured_rect::c_single_coloured_rect()
    {
		set_name(L"single_coloured_rect");
		set_logger_name(L"single_coloured_rect_logger");
    }
	void c_single_coloured_rect::init(std::shared_ptr<c_shader>& shader)
	{
		m_index_buffer.bind();

		m_index_buffer.set
		({
			0, 1, 2,
			2, 3, 0
		});

		m_shader = shader;

		m_mat4_uniform.set_uniform_name("u_aspect_ratio_projection_matrix");

		m_mat4_uniform.init(shader->shader_program_id(), m_projection);

		m_colour_uniform.set_uniform_name("u_colour");
		m_colour_uniform.init(shader->shader_program_id());
		m_colour_uniform.set(0.2f, 0.0f, 0.7f, 1.0f);

		m_vertex_buffer_layout.add_element(2);

		m_vertex_buffer.set(vertices());

		m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
    }
	void c_single_coloured_rect::draw()
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
				update_vertex_array();

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

	void c_single_coloured_rect::set(float centre_x, float centre_y, float width, float height)
	{
		m_logger << "----Setting START----\n";
		m_logger << "centre x: " << centre_x << ";  centre y:" << centre_y
			<< ";\nwidth: " << width << ";  height: " << height << '\n';
		{
			m_x = centre_x;
			m_y = centre_y;

			m_w = width;
			m_h = height;

			m_vertex_buffer.set(vertices());

			m_should_update_vertex_array = true;
			//m_vertex_array.reset();
			//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
		}
		m_logger << "----Setting OK----\n";
	}

	void c_single_coloured_rect::set(float centre_x, float centre_y, float width, float height, 
		float red, float green, float blue, float alpha)
	{
		m_logger << "----Setting START----\n";
		m_logger << "centre x: " << centre_x << ";  centre y:" << centre_y
			<< ";\nwidth: " << width << ";  height: " << height << '\n'
			<< "red: " << red << ";  green: " << green << ";  blue: " << blue << ";  alpha: " << alpha << '\n';
		{
			m_x = centre_x;
			m_y = centre_y;

			m_w = width;
			m_h = height;

			m_vertex_buffer.set(vertices());
			m_colour_uniform.set(red, green, blue, alpha);

			m_should_update_vertex_array = true;
			//m_vertex_array.reset();
			//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
		}
		m_logger << "----Setting OK----\n";
	}

	void c_single_coloured_rect::set_position(float centre_x, float centre_y)
	{
		m_logger << "----Setting position START----\n";
		m_logger << "centre x: " << centre_x << ";  centre y:" << centre_y << '\n';
		{
			m_x = centre_x;
			m_y = centre_y;

			m_vertex_buffer.set(vertices());

			m_should_update_vertex_array = true;

			//m_vertex_array.reset();
			//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
		}
		m_logger << "----Setting position OK----\n";
	}

	void c_single_coloured_rect::set_size(float width, float height)
	{
		m_logger << "----Setting size START----\n";
		m_logger << "width:" << width << ";  height:" << height << '\n';
		{
			m_w = width;
			m_h = height;

			m_vertex_buffer.set(vertices());

			m_should_update_vertex_array = true;

			//m_vertex_array.reset();
			//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
		}
		m_logger << "----Setting size OK----\n";
	}

	void c_single_coloured_rect::set_colour(float red, float green, float blue, float alpha)
	{
		m_colour_uniform.set(red, green, blue, alpha);
	}

	void c_single_coloured_rect::update_vertex_array()
	{
		if (m_should_update_vertex_array)
		{
			m_vertex_array.set_data(m_vertex_buffer, m_vertex_buffer_layout);
			m_should_update_vertex_array = false;
		}
	}
}

