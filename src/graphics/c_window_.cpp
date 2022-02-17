#include "c_window.h"


//GLFWwindow* m_glfw_window = nullptr;

namespace owd
{
	//auto c_window::m_singleton = std::make_shared<c_window>();

	static void global_frame_buffer_resize_callback(GLFWwindow* window, int frame_buffer_width, int frame_buffer_height)
	{
		glViewport(0, 0, frame_buffer_width, frame_buffer_height);
	}

	//static GLFWwindow* m_glfw_window = nullptr;

	
	bool c_window::init()
	{
		bool result = true;
		set_name(L"window");
		set_logger_name(L"window_logger");
		//m_mtx.lock();
		{
			m_logger << "Initializing window\n";
			
			m_glfw_window = glfwCreateWindow(m_w, m_h, "default glfw window", NULL, NULL);

			if (m_glfw_window == NULL)
			{
				m_logger << "glfwCreateWindow ERROR\n";
			}
			glfwMakeContextCurrent(m_glfw_window);

			glfwSwapInterval(0);

		}
		

		m_logger << "Initializing window OK\n";

		return result;
	}
	bool c_window::terminate()
	{
		bool result = true;

		//m_mtx.lock();
		{
			//m_window_exists = false;
			m_logger << "----Window closing----\n";
			glfwTerminate();
		}
		//m_mtx.unlock();

		return result;
	}
	/*void c_window::set_size(uint16_t h, uint16_t w)
	{

	}*/
	void c_window::set_fps(uint64_t fps)
	{
		//m_mtx.lock();
		{
			m_fps = fps;
		}
		//m_mtx.unlock();
	}
	uint64_t c_window::fps(uint64_t fps)
	{
		uint64_t result{};
		//m_mtx.lock();
		{
			result = m_fps;
		}
		//m_mtx.unlock();
		return result;
	}
	float c_window::refresh_period_mcs()
	{
		//float result{};
		////m_mtx.lock();
		//{
		//	result = 1000000.0f / m_fps;
		//}
		//m_mtx.unlock();
		return 1000000.0f / m_fps;;
	}
	inline int64_t c_window::refresh_period_ns()
	{
		return static_cast<int64_t>(1000000000.0f / m_fps);
	}
	void c_window::resize(uint16_t w, uint16_t h)
	{
		//m_mtx.lock();
		{
			m_logger << "Resizing window: width: " << w << ";    height: " << h << '\n';

			m_w = w;
			m_h = h;

			//glViewport(0, 0, m_w, m_h);
		}
		//m_mtx.unlock();
	}
	void c_window::run()
	{
		m_logger << "----Window running----\n";
		//m_logger << L"----Òåñò ÚúÚúúÚú----\n";
		
		while (true)
		{
			m_frame_start_time = std::chrono::high_resolution_clock::now();

			if (glfwWindowShouldClose(m_glfw_window))
			{
				m_logger << "----Window closing----\n";
				glfwTerminate();
				break;
			}
			else
			{
				m_draw_mutex.lock();
				{
					m_draw();

					/* Swap front and back buffers */
					glfwSwapBuffers(m_glfw_window);

					/* Poll for and process events */
					glfwPollEvents();
					
				}
				m_draw_mutex.unlock();
			}
			std::this_thread::sleep_for(std::chrono::nanoseconds(refresh_period_ns() -
				std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::high_resolution_clock::now() - m_frame_start_time).count()));
		}
		
	}
	void c_window::set_program(std::function<void()> program)
	{
		//m_mtx.lock();
		{
			m_logger << "Setting draw program(function)\n";
			{
				m_draw = program;
			}
			m_logger << "Setting draw program(function)\n";
		}
		//m_mtx.unlock();
	}
	void c_window::set_shader_program(uint32_t input)
	{
		m_shader_program_id = input;
	}
	float c_window::aspect_ratio()
	{
		return static_cast<float>(m_w) / static_cast<float>(m_h);
	}
	c_window::c_window()
	{
		m_logger << "----Window constructor START----\n";
		{
			init();
		}
		m_logger << "----Window constructor OK----\n";
	}
	void c_window::m_frame_buffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
	{
		//m_mtx.lock();
		{

		}
		//m_mtx.unlock();
	}
}


