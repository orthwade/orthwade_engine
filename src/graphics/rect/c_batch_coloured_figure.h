//#pragma once
//#include "../c_vertex_buffer.h"
//#include "../c_index_buffer.h"
//#include "../c_vertex_array.h"
//#include "../c_vertex_buffer_layout.h"
//#include "../c_texture.h"
//#include "../c_shader.h"
//#include "../c_texture_uniform.h"
//#include "../c_mat4_uniform.h"
//#include "../../math/glm/ext/matrix_clip_space.hpp"
//#include "../c_window.h"
//#include "../c_colour_uniform.h"
//#include "../../math/geometry/s_xy.h"
//
//namespace owd
//{
//	class c_coloured_figure : public c_basic_object
//	{
//	public:
//		enum class enm_state
//		{
//			good,
//			deleted
//		};
//		c_coloured_figure();
//		c_coloured_figure(const vertices_t vertices,
//			float red, float green, float blue, float alpha);
//
//		~c_coloured_figure();
//
//		void set(const vertices_t vertices);
//
//		void set(const vertices_t vertices,
//			float red, float green, float blue, float alpha);
//
//		void set_position(float centre_x, float centre_y);
//
//		void set_size(float magnification);
//
//		void set_colour(float red, float green, float blue, float alpha);
//
//		vertices_t& vertices()
//		{
//			return m_vertices;
//		}
//
//		bool m_should_update = false;
//
//		inline void set_to_delete() { m_state = enm_state::deleted; }
//
//		inline enm_state state() const { return m_state; }
//
//		inline bool deleted() const { return m_state == enm_state::deleted; }
//		inline xy_t centre() const { return { m_x, m_y }; }
//	private:
//		enm_state m_state = enm_state::good;
//		vertices_t m_vertices{};
//
//		float m_x{ -0.5f };
//		float m_y{ 0.0f };
//
//		float m_r{ 0.3f };
//		float m_g{ 0.8f };
//		float m_b{ 0.2f };
//		float m_a{ 1.0f };
//
//		xy_t centre(const vertices_t vertices);
//
//	};
//
//
//	class c_batch_coloured_figure : public c_basic_object
//	{
//	public:
//		void add(std::shared_ptr<c_coloured_figure>& figure);
//
//		c_batch_coloured_figure();
//
//		void init(std::shared_ptr<c_shader>& shader);
//		void draw();
//
//		std::shared_ptr<c_coloured_figure>& get_figure(index_t index);
//		void erase(index_t index);
//
//	private:
//		c_window* m_window = c_window::get_instance();
//		static std::shared_ptr<c_coloured_figure> m_empty_figure;
//
//		std::shared_ptr<c_shader> m_shader{};
//
//		c_mat4_uniform m_mat4_uniform{};
//
//		glm::mat4 m_projection = glm::ortho_(m_window->aspect_ratio());
//
//		c_vertex_buffer			m_vertex_buffer{};
//		c_index_buffer			m_index_buffer{};
//		c_vertex_array			m_vertex_array{};
//
//		c_vertex_buffer_layout	m_vertex_buffer_layout{};
//
//		bool m_should_update = false;
//		void update();
//
//		std::vector<std::shared_ptr<c_coloured_figure>> m_vec{};
//	};
//}