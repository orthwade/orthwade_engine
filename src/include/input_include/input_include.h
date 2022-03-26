#pragma once
#include <stdint.h>

namespace owd
{
	static constexpr uint8_t key_press		= 0;
	static constexpr uint8_t key_release	= 1;
	static constexpr uint8_t key_idle		= 2;

	struct s_key
	{
		int32_t		key		= 0;
		uint8_t		state	= key_idle;
	};

	s_key get_key(int32_t key_code);
	void set_key_idle(int32_t key_code);
}