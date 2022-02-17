#pragma once
#include <stdint.h>
#include "../debug/ogl_debug.h"
#include "opengl/opengl.h"
#include "../misc/c_cycle_thread.h"
#include <shared_mutex>
//#include "../misc/c_singleton.h"
#include "../misc/c_basic_object.h"

namespace owd
{
	class c_window : public c_basic_object
	{
	public:
		bool init();
		bool terminate();

		void set_fps(uint64_t fps);

		uint64_t fps(uint64_t fps);

		float refresh_period_mcs();

		inline int64_t refresh_period_ns();

		void resize(uint16_t w, uint16_t h);

		void run();

		void set_program(std::function<void()> program);

		void set_shader_program(uint32_t);

		float aspect_ratio();

		inline GLFWwindow* glfw_window()
		{
			return m_glfw_window;
		}

	private:
		c_window();

		
		//owd::c_basic_shader m_shader{};
		
		GLFWwindow* m_glfw_window = nullptr;
		int m_w = 960;
		int m_h = 540;

		int m_frame_buffer_w = 960;
		int m_frame_buffer_h = 540;

		uint32_t m_shader_program_id{};
		//c_cycle_thread m_window_thread{};

		//std::atomic_bool m_window_exists = false;
		float m_fps = 60;

		c_sleep_for_mcs m_sleep_for_mcs{};

		std::function<void()> m_draw;

		std::shared_mutex m_draw_mutex{};
		
		std::chrono::steady_clock::time_point m_frame_start_time{};
		std::chrono::steady_clock::time_point m_frame_end_time{};

		int64_t m_frame_time_ns{};

		void m_frame_buffer_resize_callback(GLFWwindow* window,
			int frame_buffe_width,
			int frame_buffe_height);

		//c_graphic_renderer* m_renderer_ptr = nullptr;
	};
}