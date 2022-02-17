#include "c_batch_coloured_circle.h"

namespace owd
{
	std::shared_ptr<c_coloured_circle> c_coloured_circle::m_empty_circle = std::shared_ptr<c_coloured_circle>();

	GLint c_coloured_circle::m_max_vertices = 0;
	GLint c_coloured_circle::m_max_indices  = 0;

	size_t c_coloured_circle::m_max_units_in_one_batch = 0;

	uint32_t c_coloured_circle::m_triangles_count = 72;

	//static auto max_units = c_coloured_circle::get_max_units();

	c_coloured_circle::c_coloured_circle()
		: c_coloured_circle(0.0f, 0.0f, 0.1f, 0.5f, 0.5f, 0.5f, 1.0f)
	{
	}

	c_coloured_circle::c_coloured_circle(float centre_x, float centre_y,
		float radius, float red, float green, float blue, float alpha)
		:
		m_x(centre_x),
		m_y(centre_y),
		m_radius(radius),
		m_r(red),
		m_g(green),
		m_b(blue),
		m_a(alpha)
	{
		update_vertices();
		for (index_t i = 0; i < m_triangles_count; ++i)
		{
			m_indices.push_back(0);
			m_indices.push_back(i + 1);
			m_indices.push_back(i + 2);
		}
		m_indices.back() = 1;
		m_indices.shrink_to_fit();
		m_should_update = true;
	}

	c_coloured_circle::~c_coloured_circle()
	{
	}

	void c_coloured_circle::set(float centre_x, float centre_y, float radius)
	{
		m_x = centre_x;
		m_y = centre_y;
		m_radius = radius;
		update_vertices();

		m_should_update = true;
	}

	void c_coloured_circle::set(float centre_x, float centre_y, float radius,
		float red, float green, float blue, float alpha)
	{
		m_x = centre_x;
		m_y = centre_y;

		m_r = red; m_g = green; m_b = blue; m_a = alpha;

		m_radius = radius;
		update_vertices();
		m_should_update = true;
	}

	void c_coloured_circle::set_position(float centre_x, float centre_y)
	{
		m_x = centre_x;
		m_y = centre_y;
		update_vertices();
		m_should_update = true;
	}

	void c_coloured_circle::set_radius(float radius)
	{
		m_radius = radius;
		update_vertices();
		m_should_update = true;
	}

	void c_coloured_circle::set_colour(float red, float green, float blue, float alpha)
	{
		m_r = red; m_g = green; m_b = blue; m_a = alpha;
		update_vertices();
		m_should_update = true;
	}

	gl_indices_t c_coloured_circle::indices()
	{
		gl_indices_t result = m_indices;

		for (index_t i = 0; i != m_indices.size(); ++i)
		{
			result[i] += m_index * (m_triangles_count + 1);
		}

		return result;
	}

	GLsizei c_coloured_circle::draw_elements_count_one_circle()
	{
		return m_triangles_count * 3;
	}

	std::shared_ptr<c_coloured_circle>& c_coloured_circle::empty_circle()
	{
		m_empty_circle = std::make_shared<c_coloured_circle>();
		return m_empty_circle;
	}

	void c_coloured_circle::update_vertices()
	{
		m_vertices.clear();

		m_angle = 90.0f + m_angle_step / 2.0f;

		m_vertices.push_back(m_x);
		m_vertices.push_back(m_y);

		m_vertices.push_back(m_r);
		m_vertices.push_back(m_g);
		m_vertices.push_back(m_b);
		m_vertices.push_back(m_a);

		for (uint16_t i = 0; i != m_triangles_count; ++i)
		{
			m_vertices.push_back(m_x + m_radius * cos_d(m_angle));
			m_vertices.push_back(m_y + m_radius * sin_d(m_angle));

			m_vertices.push_back(m_r);
			m_vertices.push_back(m_g);
			m_vertices.push_back(m_b);
			m_vertices.push_back(m_a);

			m_angle -= m_angle_step;
		}
	}

	size_t c_coloured_circle::get_max_units(GLint max_vertices, GLint max_indices)
	{
		auto var_1 = max_vertices / 6 * (1 + m_triangles_count);
		auto var_2 = max_indices / (3 * m_triangles_count);
		if (var_1 < var_2)
		{
			m_max_units_in_one_batch = var_2;
		}
		else
		{
			m_max_units_in_one_batch = var_1;
		}
		return m_max_units_in_one_batch;
	}

	void c_batch_coloured_circle::add(std::shared_ptr<c_coloured_circle>& circle)
	{
		m_vec.push_back(circle);
		m_should_update = true;
	}

	void c_batch_coloured_circle::add
	(float centre_x, float centre_y, float radius, float red, float green, float blue, float alpha)
	{
		auto circle = std::make_shared<c_coloured_circle>(centre_x, centre_y, radius,
			red, green, blue, alpha);
		add(circle);
	}

	c_batch_coloured_circle::c_batch_coloured_circle()
	{

		m_vertex_array.bind();
		m_vertex_buffer.bind();
		m_index_buffer.bind();
		

		m_vertex_buffer_layout.add_element(2);
		m_vertex_buffer_layout.add_element(4);

		m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);

		m_should_update = true;
	}
	std::shared_ptr<c_coloured_circle>& c_batch_coloured_circle::get_rect(index_t index)
	{
		if (m_vec.empty())
		{
			return c_coloured_circle::empty_circle();
		}
		else if (index < m_vec.size())
		{
			return m_vec[index];
		}
		else
		{
			return c_coloured_circle::empty_circle();
		}
	}
	void c_batch_coloured_circle::erase(index_t index)
	{
		if (m_vec.empty())
		{

		}
		else if (index < m_vec.size())
		{
			auto iter = m_vec.begin();
			iter += index;
			m_vec.erase(iter);
			m_should_update = true;
		}
		else
		{

		}
	}
	
	void c_batch_coloured_circle::draw()
	{
		//GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		// 1. ---- BINDING ----.
		{
			m_vertex_array.bind();
			//m_vertex_buffer.bind();
			//m_index_buffer.bind();
			update();
		}
		//    ---- BINDING ----.

		// 2. ---- DRAW ----
		{
			auto count_ = m_vec.size() * m_vec.back()->draw_elements_count_one_circle();
			GL_CALL(glDrawElements
			(GL_TRIANGLES, count_, GL_UNSIGNED_INT, nullptr));
		}
		//    ---- DRAW ----
	}
	void c_batch_coloured_circle::set(index_t index, float centre_x, float centre_y, float radius)
	{
		if (m_vec.empty())
		{

		}
		else if (index < m_vec.size())
		{
			m_vec[index]->set(centre_x, centre_y, radius);
		}
	}
	void c_batch_coloured_circle::set(index_t index, float centre_x, float centre_y, float radius, 
		float red, float green, float blue, float alpha)
	{
		if (m_vec.empty())
		{

		}
		else if (index < m_vec.size())
		{
			m_vec[index]->set(centre_x, centre_y, radius, red, green, blue, alpha);
		}
	}
	void c_batch_coloured_circle::set_position(index_t index, float centre_x, float centre_y)
	{
		if (m_vec.empty())
		{

		}
		else if (index < m_vec.size())
		{
			m_vec[index]->set_position(centre_x, centre_y);
		}
	}
	void c_batch_coloured_circle::set_radius(index_t index, float radius)
	{
		if (m_vec.empty())
		{

		}
		else if (index < m_vec.size())
		{
			m_vec[index]->set_radius(radius);
		}
	}
	void c_batch_coloured_circle::set_colour(index_t index, float red, float green, float blue, float alpha)
	{
		if (m_vec.empty())
		{

		}
		else if (index < m_vec.size())
		{
			m_vec[index]->set_colour(red, green, blue, alpha);
		}
	}
	void c_batch_coloured_circle::update()
	{
		for (index_t i = 0; i != m_vec.size(); ++i)
		{
			if (m_vec[i]->m_should_update)
			{
				this->m_should_update = true;
				break;
			}
		}

		m_one_circle_indices_buffer.clear();
		m_vertices_buffer.clear();
		m_indices_buffer.clear();

		for (index_t i = 0; i != m_vec.size(); ++i)
		{
			if (m_vec[i]->deleted())
			{
				auto iter = m_vec.begin();
				iter += i;
				m_vec.erase(iter);
				m_should_update = true;
			}
		}

		if (this->m_should_update)
		{
			for (index_t i = 0; i != m_vec.size(); ++i)
			{
				m_vec[i]->m_index = i;
				m_one_circle_indices_buffer = m_vec[i]->indices();

				m_vertices_buffer.insert
				(m_vertices_buffer.end(), m_vec[i]->vertices().begin(), m_vec[i]->vertices().end());

				m_indices_buffer.insert
				(m_indices_buffer.end(), m_one_circle_indices_buffer.begin(), m_one_circle_indices_buffer.end());
				m_vec[i]->m_should_update = false;
			}

			m_index_buffer.set(m_indices_buffer);
			m_vertex_buffer.set(m_vertices_buffer);

			m_vertex_array.set_data(m_vertex_buffer, m_vertex_buffer_layout);

			this->m_should_update = false;
		}
	}
	c_batches_coloured_circle::c_batches_coloured_circle()
	{
		auto shaders = c_shader_bank::get_instance();

		shaders->load(L"rsc/shaders/batch_coloured.glsl", L"batch_coloured");

		m_shader = shaders->by_filepath(L"rsc/shaders/batch_coloured.glsl");
		m_shader->bind();

		m_mat4_uniform.set_uniform_name("u_aspect_ratio_projection_matrix");

		m_mat4_uniform.init(m_shader->shader_program_id(), m_projection);

		m_max_units_one_batch = c_coloured_circle::get_max_units
		(gl_int32_param(GL_MAX_ELEMENTS_VERTICES), gl_int32_param(GL_MAX_ELEMENTS_INDICES));
	}
	c_batches_coloured_circle::c_batches_coloured_circle(GLint max_vertices, GLint max_indices)
	{
		auto shaders = c_shader_bank::get_instance();

		shaders->load(L"rsc/shaders/batch_coloured.glsl", L"batch_coloured");

		m_shader = shaders->by_filepath(L"rsc/shaders/batch_coloured.glsl");
		m_shader->bind();

		m_mat4_uniform.set_uniform_name("u_aspect_ratio_projection_matrix");

		m_mat4_uniform.init(m_shader->shader_program_id(), m_projection);

		m_max_units_one_batch = c_coloured_circle::get_max_units
		(max_vertices, max_indices);

	}
	c_batches_coloured_circle::~c_batches_coloured_circle()
	{
	}
	void c_batches_coloured_circle::add(std::shared_ptr<c_coloured_circle>& circle)
	{
		if (m_vec.empty())
		{
			auto batch = std::make_shared<c_batch_coloured_circle>();
			m_vec.push_back(batch);
		}
		else if (m_vec.size() % m_max_units_one_batch == 0)
		{
			auto batch = std::make_shared<c_batch_coloured_circle>();
			m_vec.push_back(batch);
		}
		m_vec.back()->add(circle);
	}
	void c_batches_coloured_circle::add(float centre_x, float centre_y, float radius, 
		float red, float green, float blue, float alpha)
	{
		if (m_vec.empty())
		{
			auto batch = std::make_shared<c_batch_coloured_circle>();
			m_vec.push_back(batch);
		}
		else if (m_vec.size() % m_max_units_one_batch == 0)
		{
			auto batch = std::make_shared<c_batch_coloured_circle>();
			m_vec.push_back(batch);
		}
		m_vec.back()->add(centre_x, centre_y, radius, red, green, blue, alpha);
	}
	std::shared_ptr<c_coloured_circle>& c_batches_coloured_circle::get_rect(index_t index)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
			return c_coloured_circle::empty_circle();
		}
		else
		{
			auto &local_vec = m_vec[common_and_local_index.common]->get_vec();
			return local_vec[common_and_local_index.local];
		}
	}
	void c_batches_coloured_circle::erase(index_t index)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto &local_vec = m_vec[common_and_local_index.common]->get_vec();
			auto iter = local_vec.begin();
			iter += common_and_local_index.local;
			local_vec.erase(iter);
			if (local_vec.empty())
			{
				auto iter_ = m_vec.begin();
				iter_ += common_and_local_index.common;
				m_vec.erase(iter_);
			}
		}
	}
	void c_batches_coloured_circle::clear()
	{
		m_vec.clear();
	}
	void c_batches_coloured_circle::draw()
	{
		m_shader->bind();
		for (index_t i = 0; i != m_vec.size(); ++i)
		{
			m_vec[i]->draw();
		}
	}
	void c_batches_coloured_circle::set(index_t index, float centre_x, float centre_y, float radius)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto &local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set(centre_x, centre_y, radius);
		}
	}
	void c_batches_coloured_circle::set(index_t index, float centre_x, float centre_y, float radius, 
		float red, float green, float blue, float alpha)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto &local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set(centre_x, centre_y, radius,
				red, green, blue, alpha);
		}
	}
	void c_batches_coloured_circle::set_position(index_t index, float centre_x, float centre_y)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto &local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set_position(centre_x, centre_y);
		}
	}
	void c_batches_coloured_circle::set_radius(index_t index, float radius)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto &local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set_radius(radius);
		}
	}
	void c_batches_coloured_circle::set_colour(index_t index, float red, float green, float blue, float alpha)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto &local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set_colour(red, green, blue, alpha);
		}
	}
	c_batches_coloured_circle::s_indices c_batches_coloured_circle::get_common_and_local_indices(index_t index)
	{
		index_t index_ = 0;
		auto& common_vec = m_vec;
		for (index_t i = 0; i != m_vec.size(); ++i)
		{
			auto& local_vec = m_vec[i]->get_vec();

			for (index_t ii = 0; ii != m_vec.size(); ++ii)
			{
				if (index_ == index)
				{
					return { i, static_cast<int64_t>(ii) };
				}
				++index_;
			}
		}
		return { 0, -1 };
	}
}