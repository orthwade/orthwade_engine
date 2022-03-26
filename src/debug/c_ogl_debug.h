#pragma once
#include "logger/logger.h"
#include "../graphics/opengl/opengl.h"

namespace owd_lib
{
	class c_ogl_debug
	{
	public:
		static c_ogl_debug* get_instance();
		static void terminate();

		std::wstring_view error_view(GLenum error_code);

		void gl_clear_error();

		bool gl_log_call();

	protected:
		c_logger gl_logger{ L"gl_logger" };
		std::wstring gl_error_str{};

		static c_ogl_debug* m_singleton;

		c_ogl_debug();
		~c_ogl_debug();
		
		c_ogl_debug(const c_ogl_debug&) = delete;
		c_ogl_debug& operator=(const c_ogl_debug&) = delete;
	};
}
#define GL_CALL(x)									\
{													\
	auto ogl_debug = c_ogl_debug::get_instance();	\
	ogl_debug->gl_clear_error();					\
	x;												\
	ASSERT(ogl_debug->gl_log_call())				\
}