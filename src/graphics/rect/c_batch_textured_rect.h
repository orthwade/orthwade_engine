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
#include "../c_texture_uniform.h"
#include "../c_shader_bank.h"

namespace owd
{
	class c_textured_rect : public c_basic_object
	{
	public:
		enum class enm_state
		{
			empty,
			good,
			deleted
		};
		c_textured_rect();
		c_textured_rect(float centre_x, float centre_y, float width, float height);
		c_textured_rect(float centre_x, float centre_y, float width, float height,
			std::shared_ptr<c_texture>& texture);

		~c_textured_rect();

		void set(float centre_x, float centre_y, float width, float height);

		void set(float centre_x, float centre_y, float width, float height,
			std::shared_ptr<c_texture>& texture);

		void set_position(float centre_x, float centre_y);

		void set_size(float width, float height);

		void set_texture(std::shared_ptr<c_texture>& texture);

		std::shared_ptr<c_texture>& get_texture()
		{
			return m_texture;
		}
		vertices_t vertices()
		{
			return
			{
				m_x + -m_w / 2.0f, m_y + -m_h / 2.0f,	 0.0f, 0.0f,    m_index,
				m_x +  m_w / 2.0f, m_y + -m_h / 2.0f,	 1.0f, 0.0f,    m_index,
				m_x +  m_w / 2.0f, m_y +  m_h / 2.0f,	 1.0f, 1.0f,    m_index,
				m_x + -m_w / 2.0f, m_y +  m_h / 2.0f,	 0.0f, 1.0f,    m_index
			};
		}

		bool m_should_update = false;

		float m_index = 0.0f;

		inline void set_to_delete() { m_state = enm_state::deleted; }

		inline enm_state state() { return m_state; }

		inline bool deleted() { return m_state == enm_state::deleted; }

	private:
		enm_state m_state{ enm_state::empty };
		std::shared_ptr<c_texture> m_texture{};

		float m_x{ -0.5f };
		float m_y{ 0.0f };

		float m_w{ 0.5f };
		float m_h{ 0.5f };
	};

	class c_batch_textured_rect : public c_basic_object
	{
	public:
		void add(std::shared_ptr<c_textured_rect>& rect);
		void add(float centre_x, float centre_y, float width, float height,
			std::shared_ptr<c_texture>& texture);

		c_batch_textured_rect();

		void init();
		void draw();
		size_t count();

		std::shared_ptr<c_textured_rect>& get_rect(index_t index);
		void erase(index_t index);
		void set(index_t index, float centre_x, float centre_y, float width, float height);

		void set(index_t index, float centre_x, float centre_y, float width, float height,
			std::shared_ptr<c_texture>& texture);

		void set_position(index_t index, float centre_x, float centre_y);

		void set_size(index_t index, float width, float height);

		void set_texture(index_t index, std::shared_ptr<c_texture>& texture);
		bool m_should_update = false;
		index_t m_batch_index = 0;
	private:
		c_window* m_window = c_window::get_instance();
		static std::shared_ptr<c_textured_rect> m_empty_rect;
		c_vertex_buffer			m_vertex_buffer{};
		c_index_buffer			m_index_buffer{};
		c_vertex_array			m_vertex_array{};

		c_vertex_buffer_layout	m_vertex_buffer_layout{};

		void update();

		std::vector<std::shared_ptr<c_textured_rect>> m_vec{};
	};

	class c_batches_textured
	{
	public:
		c_batches_textured();
		c_batches_textured(std::shared_ptr<c_shader>& shader, GLint max_texture_image_units);

		void init(std::shared_ptr<c_shader>& shader, GLint max_texture_image_units);

		void add(std::shared_ptr<c_textured_rect>& rect);

		void add(float centre_x, float centre_y, float width, float height,
			std::shared_ptr<c_texture>& texture);
		void draw();

		std::shared_ptr<c_textured_rect> get_rect(index_t index);

		void erase(index_t index);
		void erase(std::shared_ptr<c_textured_rect>& rect);
		void clear();

		void set(index_t index, float centre_x, float centre_y, float width, float height);

		void set(index_t index, float centre_x, float centre_y, float width, float height,
			std::shared_ptr<c_texture>& texture);

		void set_position(index_t index, float centre_x, float centre_y);

		void set_size(index_t index, float width, float height);

		void set_texture(index_t index, std::shared_ptr<c_texture>& texture);

	private:
		c_window* m_window = c_window::get_instance();

		GLint m_max_texture_image_units = 2;

		std::vector<std::shared_ptr<c_batch_textured_rect>> m_vec{};

		std::shared_ptr<c_shader> m_shader{};

		c_mat4_uniform m_mat4_uniform{};

		c_texture_uniform m_texture_uniform{};

		glm::mat4 m_projection = glm::ortho_(m_window->aspect_ratio());
	};

}