#pragma once
#include "../debug/ogl_debug.h"
#include <unordered_map>

namespace owd
{
	class c_glsl_uniform
	{
	public:
		c_glsl_uniform();
		~c_glsl_uniform(); 

		c_glsl_uniform(const c_glsl_uniform& other);
		c_glsl_uniform& operator=(const c_glsl_uniform& other);

		void set_uniform_name(std::string_view name);

		inline std::string_view uniform_name()
		{
			return m_uniform_name;
		}
		
		virtual void init(uint32_t shader_program_id) = 0;

		int32_t get_location();

	protected:
		std::wstring m_object_name{ L"glsl_uniform_object" };
		std::string m_uniform_name{ "" };
		c_logger m_logger{ L"c_glsl_uniform", enm_log_mode::none };
		std::recursive_mutex m_mtx{};

		uint32_t m_shader_program_id{};

		int32_t m_uniform_location = -1;

		//bool m_cached = false;
	};
}
