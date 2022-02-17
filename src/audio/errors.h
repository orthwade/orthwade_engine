#pragma once
#include <string_view>
#include <iostream>
#include <mutex>
#include "./openal/openal.h"
#include "c_sound_device.h"
#include "../debug/logger/logger.h"

namespace owd
{
	std::wstring openal_error_string(ALCenum error);
	
	class c_openal_check
	{
	public:
		c_openal_check();
		c_openal_check(std::wstring_view);

		c_openal_check(const c_openal_check& other);

		bool operator()(std::wstring_view input = L"");

		void set_name(std::wstring_view name);
		void set_logger_name(std::wstring_view name);

	private:
		std::wstring m_name{};

		ALCenum m_error{};
		ALCdevice* m_openal_device_ptr = nullptr;
		c_logger m_logger{L"[openal_check]"};
	};

}
