//#include "c_batch_coloured_figure.h"
//
//namespace owd
//{
//	std::shared_ptr<c_coloured_figure> c_batch_coloured_figure::m_empty_figure = std::shared_ptr<c_coloured_figure>();
//	c_coloured_figure::c_coloured_figure()
//	{
//
//	}
//
//	c_coloured_figure::c_coloured_figure
//	(const vertices_t vertices, float red, float green, float blue, float alpha)
//		:
//		m_vertices(vertices),
//		m_r(red),
//		m_g(green), 
//		m_b(blue),
//		m_a(alpha)
//	{
//		auto centre_ = centre(m_vertices);
//		m_x = centre_.x;
//		m_y = centre_.y;
//	}
//
//	c_coloured_figure::~c_coloured_figure()
//	{
//	}
//
//	void c_coloured_figure::set(const vertices_t vertices)
//	{
//		m_logger << "----Setting START----\n";
//		m_logger << "centre x: " << centre_x << ";  centre y:" << centre_y
//			<< ";\nwidth: " << width << ";  height: " << height << '\n';
//		{
//			m_x = centre_x;
//			m_y = centre_y;
//
//			m_w = width;
//			m_h = height;
//			m_should_update = true;
//		}
//		m_logger << "----Setting OK----\n";
//	}
//
//	void c_coloured_figure::set(const vertices_t vertices,
//		float red, float green, float blue, float alpha)
//	{
//		m_logger << "----Setting START----\n";
//		m_logger << "centre x: " << centre_x << ";  centre y:" << centre_y
//			<< ";\nwidth: " << width << ";  height: " << height << '\n'
//			<< "red: " << red << ";  green: " << green << ";  blue: " << blue << ";  alpha: " << alpha << '\n';
//		{
//			m_x = centre_x;
//			m_y = centre_y;
//
//			m_w = width;
//			m_h = height;
//
//			m_r = red; m_g = green; m_b = blue; m_a = alpha;
//			m_should_update = true;
//		}
//		m_logger << "----Setting OK----\n";
//	}
//
//	void c_coloured_figure::set_position(float centre_x, float centre_y)
//	{
//		m_logger << "----Setting position START----\n";
//		m_logger << "centre x: " << centre_x << ";  centre y:" << centre_y << '\n';
//		{
//			m_x = centre_x;
//			m_y = centre_y;
//			m_should_update = true;
//		}
//		m_logger << "----Setting position OK----\n";
//	}
//
//	void c_coloured_figure::set_size(float width, float height)
//	{
//		m_logger << "----Setting size START----\n";
//		m_logger << "width:" << width << ";  height:" << height << '\n';
//		{
//			m_w = width;
//			m_h = height;
//			m_should_update = true;
//		}
//		m_logger << "----Setting size OK----\n";
//	}
//
//	void c_coloured_figure::set_colour(float red, float green, float blue, float alpha)
//	{
//		m_r = red; m_g = green; m_b = blue; m_a = alpha;
//		m_should_update = true;
//	}
//
//	xy_t c_coloured_figure::centre(const vertices_t vertices)
//	{
//		xy_t xy{ 0.0f, 0.0f };
//		for (index_t i = 0; i < vertices.size(); ++i, ++i)
//		{
//			xy.x += vertices[i];
//			xy.y += vertices[i + 1];
//		}
//		xy /= (vertices.size() / 2.0f);
//		return xy;
//	}
//
//	void c_batch_coloured_figure::add(std::shared_ptr<c_coloured_figure>& figure)
//	{
//		m_vec.push_back(figure);
//		m_should_update = true;
//	}
//
//	c_batch_coloured_figure::c_batch_coloured_figure()
//	{
//		set_name(L"batch_coloured_figure");
//		set_logger_name(L"batch_coloured_figure_logger");
//	}
//	void c_batch_coloured_figure::init(std::shared_ptr<c_shader>& shader)
//	{
//		m_shader = shader;
//		m_vertex_array.bind();
//		m_vertex_buffer.bind();
//		m_index_buffer.bind();
//		m_shader->bind();
//		m_mat4_uniform.set_uniform_name("u_aspect_ratio_projection_matrix");
//
//		m_mat4_uniform.init(shader->shader_program_id(), m_projection);
//
//
//		m_vertex_buffer_layout.add_element(2);
//		m_vertex_buffer_layout.add_element(4);
//
//		m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
//	}
//	void c_batch_coloured_figure::draw()
//	{
//		//-------------------DRAW_TEXTURED_figure------------------------
//		{
//			//GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
//
//			// 1. ---- BINDING ----.
//			{
//				m_vertex_array.bind();
//				//m_vertex_buffer.bind();
//				//m_index_buffer.bind();
//				m_shader->bind();
//				update();
//
//				//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
//				//m_vertex_array.add_buffer(m_vertex_buffer, m_vertex_buffer_layout);
//			}
//			//    ---- BINDING ----.
//
//			// 2. ---- DRAW ----
//			{
//				GL_CALL(glDrawElements(GL_TRIANGLES, 6 * m_vec.size(), GL_UNSIGNED_INT, nullptr));
//			}
//			//    ---- DRAW ----
//		}
//		//-------------------DRAW_TEXTURED_figure------------------------
//	}
//	std::shared_ptr<c_coloured_figure>& c_batch_coloured_figure::get_figure(index_t index)
//	{
//		if (m_vec.empty())
//		{
//			m_empty_figure = std::make_shared<c_coloured_figure>();
//			return m_empty_figure;
//		}
//		else if (index < m_vec.size())
//		{
//			return m_vec[index];
//		}
//		else
//		{
//			m_empty_figure = std::make_shared<c_coloured_figure>();
//			return m_empty_figure;
//		}
//	}
//	void c_batch_coloured_figure::erase(index_t index)
//	{
//		if (m_vec.empty())
//		{
//
//		}
//		else if (index < m_vec.size())
//		{
//			auto iter = m_vec.begin();
//			iter += index;
//			m_vec.erase(iter);
//			m_should_update = true;
//		}
//		else
//		{
//
//		}
//	}
//	void c_batch_coloured_figure::update()
//	{
//		for (index_t i = 0; i != m_vec.size(); ++i)
//		{
//			if (m_vec[i]->m_should_update);
//			{
//				this->m_should_update = true;
//				break;
//			}
//		}
//
//		if (m_should_update)
//		{
//			std::vector<uint32_t> vec_indexes{};
//
//			uint32_t uint32_index{};
//
//			size_t figure_count = m_vec.size();
//			size_t indexes_count = 6 * figure_count;
//			vec_indexes.resize(indexes_count);
//			index_t vec_indexes_index = 0;
//
//			std::vector<float> vec_vertices{};
//			std::vector<float> vec_vertices_buffer{};
//
//			vec_vertices.resize(24 * figure_count);
//			auto vec_vertices_iter = vec_vertices.begin();
//
//			for (index_t i = 0; i != m_vec.size(); ++i)
//			{
//				if (m_vec[i]->deleted())
//				{
//					auto iter = m_vec.begin();
//					iter += i;
//					m_vec.erase(iter);
//					m_should_update = true;
//				}
//			}
//
//			for (index_t i = 0; i != m_vec.size(); ++i)
//			{
//				uint32_index = static_cast<uint32_t>(i);
//
//				vec_indexes[vec_indexes_index + 0] = 0 + 4 * uint32_index;
//				vec_indexes[vec_indexes_index + 1] = 1 + 4 * uint32_index;
//				vec_indexes[vec_indexes_index + 2] = 2 + 4 * uint32_index;
//				vec_indexes[vec_indexes_index + 3] = 2 + 4 * uint32_index;
//				vec_indexes[vec_indexes_index + 4] = 3 + 4 * uint32_index;
//				vec_indexes[vec_indexes_index + 5] = 0 + 4 * uint32_index;
//				vec_indexes_index += 6;
//
//				vec_vertices_buffer = m_vec[i]->vertices();
//				std::copy(vec_vertices_buffer.begin(), vec_vertices_buffer.end(), vec_vertices_iter);
//				vec_vertices_iter += 24;
//				m_vec[i]->m_should_update = false;
//			}
//
//			//m_vertex_array.bind();
//			//m_vertex_buffer.bind();
//			//m_index_buffer.bind();
//
//			m_index_buffer.set(vec_indexes);
//			m_vertex_buffer.set(vec_vertices);
//
//			m_vertex_array.set_data(m_vertex_buffer, m_vertex_buffer_layout);
//
//			m_should_update = false;
//		}
//	}
//}
//
