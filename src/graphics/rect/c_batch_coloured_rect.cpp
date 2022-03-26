#include "c_batch_coloured_rect.h"

namespace owd_lib
{
	std::shared_ptr<c_coloured_rect> c_coloured_rect::m_empty_rect = std::shared_ptr<c_coloured_rect>();

	GLint c_coloured_rect::m_max_vertices = 0;
	GLint c_coloured_rect::m_max_indices = 0;

	size_t c_coloured_rect::m_max_units_in_one_batch = 0;

	c_coloured_rect::c_coloured_rect()
	{

	}

	c_coloured_rect::c_coloured_rect(float centre_x, float centre_y, float width, float height, 
		float red, float green, float blue, float alpha)
	{
		set(centre_x, centre_y, width, height, red, green, blue, alpha);
	}

	c_coloured_rect::~c_coloured_rect()
	{
	}

	void c_coloured_rect::set(float centre_x, float centre_y, float width, float height)
	{
		m_x = centre_x;
		m_y = centre_y;

		m_w = width;
		m_h = height;
		m_should_update = true;
	}

	void c_coloured_rect::set(float centre_x, float centre_y, float width, float height,
		float red, float green, float blue, float alpha)
	{
		m_x = centre_x;
		m_y = centre_y;

		m_w = width;
		m_h = height;

		m_r = red; m_g = green; m_b = blue; m_a = alpha;
		m_should_update = true;
	}

	void c_coloured_rect::set_position(float centre_x, float centre_y)
	{
		m_x = centre_x;
		m_y = centre_y;
		m_should_update = true;
	}

	void c_coloured_rect::set_size(float width, float height)
	{
		m_w = width;
		m_h = height;
		m_should_update = true;
	}

	void c_coloured_rect::set_colour(float red, float green, float blue, float alpha)
	{
		m_r = red; m_g = green; m_b = blue; m_a = alpha;
		m_should_update = true;
	}

	std::shared_ptr<c_coloured_rect>& c_coloured_rect::empty_rect()
	{
		m_empty_rect = std::make_shared<c_coloured_rect>();
		return m_empty_rect;
	}

	size_t c_coloured_rect::get_max_units(GLint max_vertices, GLint max_indices)
	{
		auto var_1 = max_vertices / 24;
		auto var_2 = max_indices / 6;
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

	void c_batch_coloured_rect::add(std::shared_ptr<c_coloured_rect>& rect)
	{
		m_vec.push_back(rect);
		m_should_update = true;
	}

	void c_batch_coloured_rect::add(float centre_x, float centre_y, float width, float height, 
		float red, float green, float blue, float alpha)
	{
		auto rect = std::make_shared<c_coloured_rect>(centre_x, centre_y, width, height,
			red, green, blue, alpha);
		add(rect);
	}

	c_batch_coloured_rect::c_batch_coloured_rect()
	{
		m_vertex_array.bind();
		m_vertex_buffer.bind();
		m_index_buffer.bind();

		m_vertex_buffer_layout.add_element(2);
		m_vertex_buffer_layout.add_element(4);

		m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);

		m_should_update = true;
	}
	void c_batch_coloured_rect::draw()
	{
		//-------------------DRAW_TEXTURED_RECT------------------------
		{
			//GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

			// 1. ---- BINDING ----.
			{
				m_vertex_array.bind();
				update();
			}
			//    ---- BINDING ----.

			// 2. ---- DRAW ----
			{
				GL_CALL(glDrawElements(GL_TRIANGLES, 6 * m_vec.size(), GL_UNSIGNED_INT, nullptr));
			}
			//    ---- DRAW ----
		}
		//-------------------DRAW_TEXTURED_RECT------------------------
	}
	std::shared_ptr<c_coloured_rect>& c_batch_coloured_rect::get_rect(index_t index)
	{
		if (m_vec.empty())
		{
			return c_coloured_rect::empty_rect();
		}
		else if (index < m_vec.size())
		{
			return m_vec[index];
		}
		else
		{
			return c_coloured_rect::empty_rect();
		}
	}
	void c_batch_coloured_rect::erase(index_t index)
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
	void c_batch_coloured_rect::update()
	{
		for (index_t i = 0; i != m_vec.size(); ++i)
		{
			if(m_vec[i]->m_should_update);
			{
				this->m_should_update = true;
				break;
			}
		}

		if (m_should_update)
		{
			std::vector<uint32_t> vec_indexes{};

			uint32_t uint32_index{};

			size_t rect_count = m_vec.size();
			size_t indexes_count = 6 * rect_count;
			vec_indexes.resize(indexes_count);
			index_t vec_indexes_index = 0;

			std::vector<float> vec_vertices{};
			std::vector<float> vec_vertices_buffer{};

			vec_vertices.resize(24 * rect_count);
			auto vec_vertices_iter = vec_vertices.begin();

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

			for (index_t i = 0; i != m_vec.size(); ++i)
			{
				uint32_index = static_cast<uint32_t>(i);

				vec_indexes[vec_indexes_index + 0] = 0 + 4 * uint32_index;
				vec_indexes[vec_indexes_index + 1] = 1 + 4 * uint32_index;
				vec_indexes[vec_indexes_index + 2] = 2 + 4 * uint32_index;
				vec_indexes[vec_indexes_index + 3] = 2 + 4 * uint32_index;
				vec_indexes[vec_indexes_index + 4] = 3 + 4 * uint32_index;
				vec_indexes[vec_indexes_index + 5] = 0 + 4 * uint32_index;
				vec_indexes_index += 6;

				vec_vertices_buffer = m_vec[i]->vertices();
				std::copy(vec_vertices_buffer.begin(), vec_vertices_buffer.end(), vec_vertices_iter);
				vec_vertices_iter += 24;
				m_vec[i]->m_should_update = false;
			}

			m_index_buffer.set(vec_indexes);
			m_vertex_buffer.set(vec_vertices);

			m_vertex_array.set_data(m_vertex_buffer, m_vertex_buffer_layout);

			m_should_update = false;
		}
	}

	c_batches_coloured_rect::c_batches_coloured_rect()
	{
		auto shaders = c_shader_bank::get_instance();
		shaders->load(L"rsc/shaders/batch_coloured.glsl", L"batch_coloured");

		m_shader = shaders->by_filepath(L"rsc/shaders/batch_coloured.glsl");

		m_shader->bind();

		m_mat4_uniform.set_uniform_name("u_aspect_ratio_projection_matrix");

		m_mat4_uniform.init(m_shader->shader_program_id(), m_projection);

		m_max_units_one_batch = c_coloured_rect::get_max_units
		(gl_int32_param(GL_MAX_ELEMENTS_VERTICES), gl_int32_param(GL_MAX_ELEMENTS_INDICES));
	}

	c_batches_coloured_rect::c_batches_coloured_rect(GLint max_vertices, GLint max_indices)
	{
		auto shaders = c_shader_bank::get_instance();
		shaders->load(L"rsc/shaders/batch_coloured.glsl", L"batch_coloured");

		m_shader = shaders->by_filepath(L"rsc/shaders/batch_coloured.glsl");

		m_shader->bind();

		m_mat4_uniform.set_uniform_name("u_aspect_ratio_projection_matrix");

		m_mat4_uniform.init(m_shader->shader_program_id(), m_projection);

		m_max_units_one_batch = c_coloured_rect::get_max_units
		(max_vertices, max_indices);
	}
	c_batches_coloured_rect::~c_batches_coloured_rect()
	{
	}
	void c_batches_coloured_rect::add(std::shared_ptr<c_coloured_rect>& rect)
	{
		if (m_vec.empty())
		{
			auto batch = std::make_shared<c_batch_coloured_rect>();
			m_vec.push_back(batch);
		}
		else if (m_vec.size() % m_max_units_one_batch == 0)
		{
			auto batch = std::make_shared<c_batch_coloured_rect>();
			m_vec.push_back(batch);
		}
		m_vec.back()->add(rect);
	}
	void c_batches_coloured_rect::add(float centre_x, float centre_y, float width, float height, 
		float red, float green, float blue, float alpha)
	{
		if (m_vec.empty())
		{
			auto batch = std::make_shared<c_batch_coloured_rect>();
			m_vec.push_back(batch);
		}
		else if (m_vec.size() % m_max_units_one_batch == 0)
		{
			auto batch = std::make_shared<c_batch_coloured_rect>();
			m_vec.push_back(batch);
		}
		m_vec.back()->add(centre_x, centre_y, width, height, red, green, blue, alpha);
	}
	
	std::shared_ptr<c_coloured_rect>& c_batches_coloured_rect::get_rect(index_t index)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
			return c_coloured_rect::empty_rect();
		}
		else
		{
			auto& local_vec = m_vec[common_and_local_index.common]->get_vec();
			return local_vec[common_and_local_index.local];
		}
	}
	void c_batches_coloured_rect::erase(index_t index)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto& local_vec = m_vec[common_and_local_index.common]->get_vec();
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
	void c_batches_coloured_rect::clear()
	{
		m_vec.clear();
	}
	void c_batches_coloured_rect::draw()
	{
		m_shader->bind();
		for (index_t i = 0; i != m_vec.size(); ++i)
		{
			m_vec[i]->draw();
		}
	}
	void c_batches_coloured_rect::set(index_t index, float centre_x, float centre_y, float width, float height)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto& local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set(centre_x, centre_y, width, height);
		}
	}
	void c_batches_coloured_rect::set(index_t index, float centre_x, float centre_y, float width, float height, 
		float red, float green, float blue, float alpha)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto& local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set(centre_x, centre_y, width, height,
				red, green, blue, alpha);
		}
	}
	void c_batches_coloured_rect::set_position(index_t index, float centre_x, float centre_y)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto& local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set_position(centre_x, centre_y);
		}
	}
	void c_batches_coloured_rect::set_size(index_t index, float width, float height)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto& local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set_size(width, height);
		}
	}
	void c_batches_coloured_rect::set_colour(index_t index, float red, float green, float blue, float alpha)
	{
		auto common_and_local_index = get_common_and_local_indices(index);
		if (common_and_local_index.local == -1)
		{
		}
		else
		{
			auto& local_vec = m_vec[common_and_local_index.common]->get_vec();
			local_vec[common_and_local_index.local]->set_colour(red, green, blue, alpha);
		}
	}
	c_batches_coloured_rect::s_indices c_batches_coloured_rect::get_common_and_local_indices(index_t index)
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