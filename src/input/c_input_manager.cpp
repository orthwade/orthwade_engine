#include "c_input_manager.h"

namespace owd
{
	c_input_manager* c_input_manager::m_singleton = nullptr;
	
	c_input_manager* owd::c_input_manager::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_input_manager();
		}

		return m_singleton;
	}
	void c_input_manager::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
			m_singleton->m_thread_exists = false;
			if (m_singleton->m_thread.joinable())
			{
				m_singleton->m_thread.join();
			}
			delete m_singleton;
			m_singleton = nullptr;
		}
	}
	void c_input_manager::add_action(int32_t key_code, enm_key_state key_state, std::function<void()> action)
	{
		m_actions.push_back({key_code, key_state, action});
	}
	s_key& c_input_manager::get_key(int32_t key_code)
	{
		for (index_t i = 0; i != m_keys.size(); ++i)
		{
			if (m_keys[i].key == key_code)
			{
				return m_keys[i];
			}
		}
		
		m_keys.push_back({ key_code, key_release });
		return m_keys.back();
	}
	void c_input_manager::thread_function()
	{
		while (m_thread_exists.load())
		{
			m_thread_mutex.lock();
			{
				for (index_t i = 0; i != m_actions.size(); ++i)
				{
					if (m_actions[i].active())
					{
						auto& key_ = get_key(m_actions[i].gey_key().key);
						if (key_.state == key_idle)
						{

						}
						else
						{
							if (m_actions[i].gey_key().state == key_.state)
							{
								m_actions[i].do_();
								key_.state = key_idle;
							}
						}
					}
				}
			}
			m_thread_mutex.unlock();
		}
	}
	c_input_manager::c_input_manager()
		:
		m_thread(std::bind(&c_input_manager::thread_function, this))
    {
		glfwSetKeyCallback(c_window::get_instance()->glfw_window(), key_callback);
    }
    c_input_manager::~c_input_manager()
    {
    }
	void key_callback(GLFWwindow* window, int32_t key_code, int32_t scancode, int32_t action, int32_t mods)
	{
		auto input_manager = c_input_manager::get_instance();
		auto& key_ = input_manager->get_key(key_code);
		key_.key = key_code;
		if (action == GLFW_PRESS)
		{
			key_.state = key_press;
		}
		else
		{
			key_.state = key_release;
		}
	}
	c_action::c_action(int32_t key_code, enm_key_state key_state, std::function<void()> action)
		:
		m_key({ key_code, key_state }),
		m_action(action),
		m_enabled(true)
	{
		
	}
}