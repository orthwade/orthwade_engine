#pragma once
#include <mutex>
#include <string_view>

namespace owd_lib
{
	/// <summary>
	/// Graphic entity. Entity to be drawn.
	/// </summary>
	class c_g_entity
	{
	public:
		c_g_entity();
		~c_g_entity();

		//c_g_entity(const c_g_entity& other);
		//c_g_entity& operator=(const c_g_entity& other);

		inline bool should_draw();

	private:
		bool m_should_draw = false;
	};
}