#pragma once
#include "../debug/ogl_debug.h"
#include "../misc/misc_defines.h"

namespace owd
{
	typedef std::vector<float> vertices_t;
	class c_vertex_buffer
	{
	public:
		c_vertex_buffer();
		//c_vertex_buffer(std::vector<float>& vertices);
		~c_vertex_buffer();

		c_vertex_buffer(const c_vertex_buffer& other);
		c_vertex_buffer& operator=(const c_vertex_buffer& other);

		void set_name(std::wstring_view name);

		std::wstring_view name()
		{
			return m_name;
		}

		void init();
		void terminate();

		void set(const std::vector<float>& vertices);
		void add(const std::vector<float>& vertices);

		void bind();

		void unbind();

		inline void* data()
		{
			return reinterpret_cast<void*>(m_vertex_positions_data->data());
		}

		inline size_t size()
		{
			return m_vertex_positions_data->size();
		}

	private:
		std::wstring m_name{ L"c_vertex_buffer" };

		c_logger m_logger{ L"c_vertex_buffer", enm_log_mode::none };

		std::mutex m_mtx{};

		uint32_t m_ogl_id{};

		//uint32_t m_vertex_array_ogl_id{};

		data_t m_vertex_positions_data = std::make_shared<bytes_t>();
	};
}