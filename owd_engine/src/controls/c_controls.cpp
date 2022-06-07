#include "c_controls.h"

namespace owd
{
    static action_t static_action_buffer{};
    static action_t empty_action_buffer{};
    std::wstring c_action::m_empty_string{ L"" };

    c_action::c_action(int32_t key_code, wstr_func_t& action, std::wstring_view name)
        :
        m_key(key_code),
        m_action(action),
        m_name(name)
    {
    }
    action_t& c_action::empty_action()
    {
        wstr_func_t empty_action_ = []() { return empty_string(); };
        empty_action_buffer = make_action(-1, empty_action_, L"empty_action");
        return empty_action_buffer;
    }
    std::wstring_view c_action::empty_string()
    {
        return m_empty_string;
    }
    action_t& make_action(int32_t key_code, wstr_func_t& action, std::wstring_view name)
    {
        static_action_buffer = std::make_shared<c_action>(key_code, action, name);
        return static_action_buffer;
    }
    action_t& c_controls::add_action(int32_t key_code, wstr_func_t& action, std::wstring_view name)
    {
        for (auto& action : m_vec_actions)
        {
            if (strings_are_equal(action->name(), name))
            {
                return action;
            }
        }
        auto action_ = make_action(key_code, action, name);
        m_vec_actions.push_back(action_);
        return m_vec_actions.back();
    }
    action_t& c_controls::get_action(std::wstring_view name)
    {
        for (auto& action : m_vec_actions)
        {
            if (strings_are_equal(action->name(), name))
            {
                return action;
            }
        }
        return c_action::empty_action();
    }
    action_t& c_controls::last_action()
    {
        if (m_vec_actions.empty())
        {
            return c_action::empty_action();
        }
        else
        {
            return m_vec_actions.back();
        }
    }
    void c_controls::init()
    {
        m_thread_exists.store(true);
        m_thread = std::thread(&c_controls::thread_function, this);
    }
    void c_controls::run()
    {
        m_run.store(true);
    }
    void c_controls::stop()
    {
        m_run.store(false);
    }
    void c_controls::disable_controls()
    {
        std::mutex mtx{};
        auto lock = std::lock_guard(mtx);
        for (auto& action : m_vec_actions)
        {
            action->disable();
        }
    }
    void c_controls::thread_function()
    {
        while (true)
        {
            if (!m_thread_exists.load())
            {
                break;
            }
            if (m_run.load())
            {
                auto lock = std::lock_guard(m_thread_mutex);
                for (auto& action : m_vec_actions)
                {
                    if (action->is_enabled())
                    {
                        auto key = get_key(action->key());
                        if (key.state == key_press)
                        {
                            action->do_();
                            set_key_idle(key.key);
                        }
                    }
                }
            }
            sleep_for_ms(1);
        }
    }
}

namespace owd
{
	c_controls* c_controls::m_singleton = nullptr;
	
	c_controls* owd::c_controls::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_controls();
		}

		return m_singleton;
	}
	void c_controls::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
            m_singleton->m_thread_exists = false;
            if(m_singleton->m_thread.joinable())
            {
                m_singleton->m_thread.join();
            }
			delete m_singleton;
			m_singleton = nullptr;
		}
	}
    c_controls::c_controls()
    {
    }
    c_controls::~c_controls()
    {
    }
}
