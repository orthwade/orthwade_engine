#pragma once
#include "logger/logger.h"
#include "../audio/openal/openal.h"

namespace owd
{
	class c_oal_debug
	{
	public:
		static c_oal_debug* get_instance();
		static void terminate();

		std::wstring_view error_view(ALenum error_code);

		bool al_log_call();

	protected:
		c_logger al_logger{ L"al_logger" };
		std::wstring al_error_str{};

		static c_oal_debug* m_sinaleton;

		c_oal_debug();
		~c_oal_debug();

		c_oal_debug(const c_oal_debug&) = delete;
		c_oal_debug& operator=(const c_oal_debug&) = delete;
	};
}
#define AL_CALL(x)									\
{													\
	auto oal_debug = c_oal_debug::get_instance();	\
	x;												\
	ASSERT(oal_debug->al_log_call())				\
}