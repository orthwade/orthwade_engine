#include "c_graphic_unit_textured.h"

namespace owd
{
	std::shared_ptr<c_graphic_unit_textured> c_graphic_unit_textured::m_empty_unit = std::shared_ptr<c_graphic_unit_textured>();

	GLint c_graphic_unit_textured::m_max_vertices = 0;
	GLint c_graphic_unit_textured::m_max_indices = 0;

	size_t c_graphic_unit_textured::m_max_units_in_one_batch = 0;

	gl_indices_t c_graphic_unit_textured::m_indices{ 0, 1, 2, 2, 3, 0 };

	c_graphic_unit_textured::c_graphic_unit_textured()
	{
		m_should_update = true;
	}

	c_graphic_unit_textured::c_graphic_unit_textured(float centre_x, float centre_y, float width, float height,
		texture_t& texture, uint16_t level)
		:
		m_x(centre_x),
		m_y(centre_y),
		m_centre(m_x, m_y),
		m_w(width),
		m_h(height),
		m_texture(texture),
		m_level(level),
		m_should_update(true),
		m_state(enm_state::good)
	{
		
	}

	void c_graphic_unit_textured::set_position(float centre_x, float centre_y)
	{
		m_x = centre_x;
		m_y = centre_y;
		m_centre = { centre_x, centre_y };
		m_should_update = true;
	}

	vertices_t c_graphic_unit_textured::vertices()
	{
			return
			{
				m_x + -m_w / 2.0f, m_y + -m_h / 2.0f,	 0.0f, 0.0f,    m_index,
				m_x +  m_w / 2.0f, m_y + -m_h / 2.0f,	 1.0f, 0.0f,    m_index,
				m_x +  m_w / 2.0f, m_y +  m_h / 2.0f,	 1.0f, 1.0f,    m_index,
				m_x + -m_w / 2.0f, m_y +  m_h / 2.0f,	 0.0f, 1.0f,    m_index
			};
	}

	vertices_t c_graphic_unit_textured::vertex_positions()
	{
			return
			{
				m_x + -m_w / 2.0f, m_y + -m_h / 2.0f,
				m_x +  m_w / 2.0f, m_y + -m_h / 2.0f,
				m_x +  m_w / 2.0f, m_y +  m_h / 2.0f,
				m_x + -m_w / 2.0f, m_y +  m_h / 2.0f,
			};
	}

	gl_indices_t c_graphic_unit_textured::indices_batch(gl_index_t max_index)
	{
		gl_indices_t result = m_indices;
		// 0, 1, 0, 2,  0, 3,  0, 1
		// 4, 5, 4, 6,  4, 7,  4, 5
		// 8, 9, 8, 10, 8, 11, 8, 9
		gl_index_t increment = 0;
		if (max_index == 0)
		{
			increment = 0;
		}
		else
		{
			increment = max_index + 1;
		}
		for (index_t i = 0; i != m_indices.size(); ++i)
		{
			result[i] += increment;
		}

		return result;
	}

	std::shared_ptr<c_graphic_unit_textured>& c_graphic_unit_textured::empty_unit()
	{
		m_empty_unit = std::make_shared<c_graphic_unit_textured>();
		return m_empty_unit;
	}

	xy_t c_graphic_unit_textured::centre(const vertices_t& vertex_positions)
	{
		xy_t result{ 0.0f, 0.0f };

		size_t vertices_count = vertex_positions.size() / 2;

		for (index_t i = 0; i < vertices_count; ++i, ++i)
		{
			result += { vertex_positions[i], vertex_positions[i + 1] };
		}

		result /= static_cast<float>(vertices_count);

		return result;
	}
}