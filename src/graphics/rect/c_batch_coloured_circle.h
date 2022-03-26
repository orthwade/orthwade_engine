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
#include "../../math/geometry/s_xy.h"
#include "../c_shader_bank.h"
#include "c_graphic_unit.h"

namespace owd_lib
{
	class c_coloured_circle
	{
	public:
		c_coloured_circle();
		c_coloured_circle(float centre_x, float centre_y, float radius,
			float red, float green, float blue, float alpha);

		~c_coloured_circle();

		void set(float centre_x, float centre_y, float radius);

		void set(float centre_x, float centre_y, float radius,
			float red, float green, float blue, float alpha);

		void set_position(float centre_x, float centre_y);

		void set_radius(float radius);

		void set_colour(float red, float green, float blue, float alpha);

		vertices_t& vertices()
		{
			return m_vertices;
		}
		bool m_should_update = false;

		xy_t centre()
		{
			return { m_x, m_y };
		}

		gl_indices_t indices();

		gl_index_t m_index = 0;

		enum class enm_state
		{
			good,
			deleted
		};

		GLsizei draw_elements_count_one_circle();

		inline void set_to_delete() { m_state = enm_state::deleted; }

		inline enm_state state() { return m_state; }

		inline bool deleted() { return m_state == enm_state::deleted; }

		static std::shared_ptr<c_coloured_circle>& empty_circle();
		static size_t get_max_units(GLint max_vertices, GLint max_indices);

	private:
		static GLint m_max_vertices;
		static GLint m_max_indices;
		static size_t m_max_units_in_one_batch;

		static std::shared_ptr<c_coloured_circle> m_empty_circle;

		vertices_t m_vertices{};
		enm_state m_state = enm_state::good;

		gl_indices_t m_indices{};

		float m_x{ -0.5f };
		float m_y{ 0.0f };

		float m_radius{ 0.1f };

		float m_r{ 0.3f };
		float m_g{ 0.8f };
		float m_b{ 0.2f };
		float m_a{ 1.0f };

		static uint32_t m_triangles_count;

		float m_angle_step = 360.0f / m_triangles_count;
		float m_angle = 90.0f + m_angle_step / 2.0f;

		void update_vertices();
	};

	class c_batch_coloured_circle
	{
	public:
		void add(std::shared_ptr<c_coloured_circle>& circle);
		void add(float centre_x, float centre_y, float radius,
			float red, float green, float blue, float alpha);

		c_batch_coloured_circle();

		std::shared_ptr<c_coloured_circle>& get_rect(index_t index);
		inline std::vector<std::shared_ptr<c_coloured_circle>>& get_vec() { return m_vec; }
		void erase(index_t index);

		void draw();

		void set			(index_t index, float centre_x, float centre_y, float radius);
		void set			(index_t index, float centre_x, float centre_y, float radius, 
			float red, float green, float blue, float alpha);
		void set_position	(index_t index, float centre_x, float centre_y);
		void set_radius		(index_t index, float radius);
		void set_colour		(index_t index, float red, float green, float blue, float alpha);

	private:

		std::vector<float>		m_vertices_buffer{};
		std::vector<uint32_t>	m_indices_buffer{};
		std::vector<uint32_t>	m_one_circle_indices_buffer{};

		c_vertex_buffer m_vertex_buffer{};
		c_index_buffer	m_index_buffer {};
		c_vertex_array	m_vertex_array {};

		c_vertex_buffer_layout	m_vertex_buffer_layout{};

		bool m_should_update = false;
		void update();
		std::vector<std::shared_ptr<c_coloured_circle>> m_vec{};
	};

	class c_batches_coloured_circle
	{
	public:
		c_batches_coloured_circle();
		c_batches_coloured_circle(GLint max_vertices, GLint max_indices);
		~c_batches_coloured_circle();
	
		void add(std::shared_ptr<c_coloured_circle>& circle);
		void add(float centre_x, float centre_y, float radius,
			float red, float green, float blue, float alpha);

		std::shared_ptr<c_coloured_circle>& get_rect(index_t index);
		void erase(index_t index);
		void clear();

		void draw();

		void set(index_t index, float centre_x, float centre_y, float radius);
		void set(index_t index, float centre_x, float centre_y, float radius,
			float red, float green, float blue, float alpha);
		void set_position(index_t index, float centre_x, float centre_y);
		void set_radius(index_t index, float radius);
		void set_colour(index_t index, float red, float green, float blue, float alpha);

	private:
		struct s_indices
		{
			uint64_t common =  0;
			int64_t  local  = -1;
		};
		c_window* m_window = c_window::get_instance();

		glm::mat4 m_projection = glm::ortho_(m_window->aspect_ratio());

		std::shared_ptr<c_shader> m_shader{};

		c_mat4_uniform m_mat4_uniform{};

		std::vector<std::shared_ptr<c_batch_coloured_circle>> m_vec{};
		
		size_t m_max_units_one_batch = 0;

		s_indices get_common_and_local_indices(index_t index);

	};
}