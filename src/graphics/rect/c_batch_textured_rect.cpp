#include "c_batch_textured_rect.h"

namespace owd_lib
{
	std::shared_ptr<c_textured_rect> c_batch_textured_rect::m_empty_rect = std::shared_ptr<c_textured_rect>();
	c_textured_rect::c_textured_rect()
	{
		set_name(L"textured_rect_to_be_batched");
		set_logger_name(L"textured_rect_to_be_batched_logger");
	}

	c_textured_rect::c_textured_rect(float centre_x, float centre_y, float width, float height)
	{
		set_name(L"textured_rect_to_be_batched");
		set_logger_name(L"textured_rect_to_be_batched_logger");
		set(centre_x, centre_y, width, height);
	}

	c_textured_rect::c_textured_rect(float centre_x, float centre_y, float width, float height, 
		std::shared_ptr<c_texture>& texture)
	{
		set_name(L"textured_rect_to_be_batched");
		set_logger_name(L"textured_rect_to_be_batched_logger");
		set(centre_x, centre_y, width, height, texture);
		m_state = enm_state::good;
	}

	c_textured_rect::~c_textured_rect()
	{
	}

	void c_textured_rect::set(float centre_x, float centre_y, float width, float height)
	{
		m_x = centre_x;
		m_y = centre_y;

		m_w = width;
		m_h = height;
		m_should_update = true;
	}

	void c_textured_rect::set(float centre_x, float centre_y, float width, float height,
		std::shared_ptr<c_texture>& texture)
	{
		m_x = centre_x;
		m_y = centre_y;

		m_w = width;
		m_h = height;

		m_texture = texture;
		m_should_update = true;
		m_state = enm_state::good;
	}

	void c_textured_rect::set_position(float centre_x, float centre_y)
	{
		m_x = centre_x;
		m_y = centre_y;
		m_should_update = true;
	}

	void c_textured_rect::set_size(float width, float height)
	{
		m_w = width;
		m_h = height;
		m_should_update = true;
	}

	void c_textured_rect::set_texture(std::shared_ptr<c_texture>& texture)
	{
		m_texture = texture;
		m_state = enm_state::good;
	}

	void c_batch_textured_rect::add(std::shared_ptr<c_textured_rect>& rect)
	{
		rect->m_index = static_cast<float>(m_vec.size());
		m_vec.push_back(rect);
		m_should_update = true;
	}

	void c_batch_textured_rect::add
	(float centre_x, float centre_y, float width, float height, std::shared_ptr<c_texture>& texture)
	{
		auto rect = std::make_shared<c_textured_rect>(centre_x, centre_y, width, height, texture);
		add(rect);
	}

	c_batch_textured_rect::c_batch_textured_rect()
	{
		set_name(L"batch_textured_rect");
		set_logger_name(L"batch_textured_rect_logger");
	}
	void c_batch_textured_rect::init()
	{
		m_vertex_array.bind();
		m_vertex_buffer.bind();
		m_index_buffer.bind();

		m_vertex_buffer_layout.add_element(2);
		m_vertex_buffer_layout.add_element(2);
		m_vertex_buffer_layout.add_element(1);

		m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
	}
	void c_batch_textured_rect::draw()
	{
		//-------------------DRAW_TEXTURED_RECT------------------------
		{
			//GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

			// 1. ---- BINDING ----.
			{
				m_vertex_array.bind();
				//m_vertex_buffer.bind();
				m_index_buffer.bind();
				update();

				for (index_t i = 0; i != m_vec.size(); ++i)
				{
					GL_CALL(glBindTextureUnit(i, m_vec[i]->get_texture()->gl_id()));
				}

				//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
				//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
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
	size_t c_batch_textured_rect::count()
	{
		return m_vec.size();
	}
	std::shared_ptr<c_textured_rect>& c_batch_textured_rect::get_rect(index_t index)
	{
		if (m_vec.empty())
		{
			m_empty_rect = std::make_shared<c_textured_rect>();
			return m_empty_rect;
		}
		else if (index < m_vec.size())
		{
			return m_vec[index];
		}
		else
		{
			m_empty_rect = std::make_shared<c_textured_rect>();
			return m_empty_rect;
		}
	}
	void c_batch_textured_rect::erase(index_t index)
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
	void c_batch_textured_rect::set(index_t index, float centre_x, float centre_y, float width, float height)
	{
		auto rect = get_rect(index);
		rect->set(centre_x, centre_y, width, height);
	}
	void c_batch_textured_rect::set
	(index_t index, float centre_x, float centre_y, float width, float height, std::shared_ptr<c_texture>& texture)
	{
		auto rect = get_rect(index);
		rect->set(centre_x, centre_y, width, height, texture);
	}
	void c_batch_textured_rect::set_position(index_t index, float centre_x, float centre_y)
	{
		auto rect = get_rect(index);
		rect->set_position(centre_x, centre_y);
	}
	void c_batch_textured_rect::set_size(index_t index, float width, float height)
	{
		auto rect = get_rect(index);
		rect->set_size(width, height);
	}
	void c_batch_textured_rect::set_texture(index_t index, std::shared_ptr<c_texture>& texture)
	{
		auto rect = get_rect(index);
		rect->set_texture(texture);
	}
	void c_batch_textured_rect::update()
	{
		for (index_t i = 0; i != m_vec.size(); ++i)
		{
			if((m_vec[i]->m_should_update) == true)
			{
				this->m_should_update = true;
				break;
			}
			else
			{

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

			vec_vertices.resize(m_vec.back()->vertices().size() * rect_count);

			auto vec_vertices_iter = vec_vertices.begin();

			for (index_t i = 0; i != m_vec.size(); ++i)
			{
				if (m_vec[i]->state() == c_textured_rect::enm_state::deleted)
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

				m_vec[i]->m_index = static_cast<float>(i);
				vec_vertices_buffer = m_vec[i]->vertices();

				std::copy(vec_vertices_buffer.begin(), vec_vertices_buffer.end(), vec_vertices_iter);

				vec_vertices_iter += vec_vertices_buffer.size();

				m_vec[i]->m_should_update = false;
			}
			
			m_index_buffer.set(vec_indexes);
			m_vertex_buffer.set(vec_vertices);

			m_vertex_array.set_data(m_vertex_buffer, m_vertex_buffer_layout);

			this->m_should_update = false;
		}
	}

	c_batches_textured::c_batches_textured()
	{
		auto shaders = c_shader_bank::get_instance();
		shaders->load(L"rsc/shaders/batch_textured.glsl", L"batch_textured");
		auto shader_ = shaders->by_filepath(L"rsc/shaders/batch_textured.glsl");
		GL_CALL(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_max_texture_image_units));
		init(shader_, m_max_texture_image_units);
	}
	c_batches_textured::c_batches_textured(std::shared_ptr<c_shader>& shader, GLint max_texture_image_units)
	{
		init(shader, max_texture_image_units);
	}
	void c_batches_textured::init(std::shared_ptr<c_shader>& shader, GLint max_texture_image_units)
	{
		m_shader = shader;
		m_max_texture_image_units = max_texture_image_units;
		m_shader->bind();
		m_mat4_uniform.set_uniform_name("u_aspect_ratio_projection_matrix");

		m_mat4_uniform.init(shader->shader_program_id(), m_projection);

		m_texture_uniform.set_uniform_name("u_textures");
		std::vector<int32_t> samplers{};
		for (index_t i = 0; i != 128; ++i)
		{
			samplers.push_back(i);
		}
		m_texture_uniform.init(shader->shader_program_id(), samplers);
	}
	void c_batches_textured::add(std::shared_ptr<c_textured_rect>& rect)
	{
		if (m_vec.empty())
		{
			auto batch = std::make_shared<c_batch_textured_rect>();
			batch->init();
			m_vec.push_back(batch);
		}
		else if (m_vec.back()->count() % m_max_texture_image_units == 0)
		{
			auto batch = std::make_shared<c_batch_textured_rect>();
			batch->init();
			m_vec.push_back(batch);
		}
		m_vec.back()->add(rect);
	}
	void c_batches_textured::add
	(float centre_x, float centre_y, float width, float height, std::shared_ptr<c_texture>& texture)
	{
		if (m_vec.empty())
		{
			auto batch = std::make_shared<c_batch_textured_rect>();
			batch->init();
			m_vec.push_back(batch);
		}
		else if (m_vec.back()->count() % m_max_texture_image_units == 0)
		{
			auto batch = std::make_shared<c_batch_textured_rect>();
			batch->init();
			m_vec.push_back(batch);
		}
		m_vec.back()->add(centre_x, centre_y, width, height, texture);
	}
	void c_batches_textured::draw()
	{
		m_shader->bind();
		for (index_t i = 0; i != m_vec.size(); ++i)
		{
			m_vec[i]->draw();
		}
	}
	std::shared_ptr<c_textured_rect> c_batches_textured::get_rect(index_t index)
	{
		auto result = std::make_shared<c_textured_rect>();

		index_t common_index{};
		index_t local_index{};

		common_index = (index) / m_max_texture_image_units;
		local_index = index - common_index * m_max_texture_image_units;

		auto& common_vec = m_vec;

		if (common_vec.empty())
		{

		}
		else
		{
			if (common_index < common_vec.size())
			{
				auto& local_vec = common_vec[common_index];

				if (local_index < local_vec->count())
				{
					result = local_vec->get_rect(local_index);
				}
			}
		}
		return result;
	}
	void c_batches_textured::erase(index_t index)
	{
		index_t common_index{};
		index_t local_index{};

		common_index = (index) / m_max_texture_image_units;
		local_index = index - common_index * m_max_texture_image_units;

		auto& common_vec = m_vec;

		if (common_vec.empty())
		{

		}
		else
		{
			if (common_index < common_vec.size())
			{
				auto& local_vec = common_vec[common_index];

				if (local_index < local_vec->count())
				{
					local_vec->erase(local_index);

					if (local_vec->count() == 0)
					{
						auto iter = common_vec.begin();
						iter += common_index;
						common_vec.erase(iter);
					}
				}
			}
		}
	}
	void c_batches_textured::erase(std::shared_ptr<c_textured_rect>& rect)
	{
		index_t common_index = 0;
		index_t local_index = 0;

		auto& common_vec = m_vec;

		if (common_vec.empty())
		{

		}
		else
		{
			for (index_t common_index = 0; common_index != common_vec.size(); ++common_index)
			{
				auto& local_vec = common_vec[common_index];
				for (index_t local_index = 0; local_index != local_vec->count(); ++local_index)
				{
					auto rect_ = local_vec->get_rect(local_index);
					if (rect_.get() == rect.get())
					{
						local_vec->erase(local_index);

						if (local_vec->count() == 0)
						{
							auto iter = common_vec.begin();
							iter += common_index;
							common_vec.erase(iter);
						}
					}
				}
			}
		}
	}
	void c_batches_textured::clear()
	{
		m_vec.clear();
	}
	void c_batches_textured::set(index_t index, float centre_x, float centre_y, float width, float height)
	{
		get_rect(index)->set(centre_x, centre_y, width, height);
	}
	void c_batches_textured::set(index_t index, float centre_x, float centre_y, float width, float height,
		std::shared_ptr<c_texture>& texture)
	{
		get_rect(index)->set(centre_x, centre_y, width, height, texture);
	}
	void c_batches_textured::set_position(index_t index, float centre_x, float centre_y)
	{
		get_rect(index)->set_position(centre_x, centre_y);
	}
	void c_batches_textured::set_size(index_t index, float width, float height)
	{
		get_rect(index)->set_size(width, height);
	}
	void c_batches_textured::set_texture(index_t index, std::shared_ptr<c_texture>& texture)
	{
		get_rect(index)->set_texture(texture);
	}

}

