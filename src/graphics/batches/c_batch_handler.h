#pragma once
#include "c_graphic_batch.h"
#include "c_graphic_batch_textured.h"
#include "../c_texture_uniform.h"

namespace owd_lib
{
	typedef std::shared_ptr<c_graphic_batch> g_batch_t;
	typedef std::shared_ptr<c_graphic_batch_textured> g_batch_textured_t;
	struct s_level
	{
		std::vector<g_batch_t>          batches{};
		std::vector<g_batch_textured_t> batches_textured{};
	};
	class c_batch_handler
	{
	public:
		s_level& get_level(uint16_t level);
		index_t add(g_unit_t& unit);
		index_t add(g_unit_textured_t& unit);

		index_t add_rect(float centre_x, float centre_y, float width, float height,
			float red, float green, float blue, float alpha, uint16_t level);

		index_t add_circle(float centre_x, float centre_y, float radius,
			float red, float green, float blue, float alpha, uint16_t level);

		index_t add_textured(float centre_x, float centre_y, float width, float height,
			texture_t& texture, uint16_t level);

		void delete_by_index(index_t index);

		g_unit_t& get_unit_by_index(index_t index);
		g_unit_textured_t& get_textured_unit_by_index(index_t index);

		void clear();
		void draw();

		static c_batch_handler* get_instance();
		static void terminate();

	private:
		index_t m_last_index = 0;
		GLint m_max_vertices{};
		GLint m_max_indices{};

		std::vector<s_level> m_levels{};
	
		c_window* m_window = c_window::get_instance();

		shader_t m_shader_coloured{};
		shader_t m_shader_textured{};

		c_texture_uniform m_texture_uniform{};

		c_mat4_uniform m_mat4_uniform_coloured{};
		c_mat4_uniform m_mat4_uniform_textured{};

		glm::mat4 m_projection = glm::ortho_(m_window->aspect_ratio());

		GLint m_max_texture_image_units = 2;

		//std::pair<uint32_t, int32_t> get_common_and_local_indices(index_t index);

		bool vertices_exceed(g_batch_t& batch, g_unit_t& unit);
		bool indices_exceed(g_batch_t& batch, g_unit_t& unit);
		bool units_count_exceeds(g_batch_t& batch, g_unit_t& unit);

		static c_batch_handler* m_singleton;

		c_batch_handler();
		~c_batch_handler();

		c_batch_handler(const c_batch_handler&) = delete;
		c_batch_handler& operator=(const c_batch_handler&) = delete;

	};
}