#include <iostream>

#include "c_pipeline.h"

namespace owd
{
    std::wstring c_stage::m_empty_string{ L"" };
    c_stage::c_stage(std::wstring_view name, wstr_func_t& initial_action)
        :
        m_name(name),
        m_initial_action(initial_action)
    {
    }
    action_t& c_stage::add_controls(int32_t key_code, wstr_func_t& action, std::wstring_view name)
    {
        auto controls = m_controls->add_action(key_code, action, name);

        for (auto& action_ : m_vec_controls)
        {
            if (strings_are_equal(action_->name(), controls->name()))
            {
                return action_;
            }
        }

        m_vec_controls.push_back(controls);
        return m_vec_controls.back();
    }
    action_t& c_stage::add_controls(action_t& action)
    {
        for (auto& action_ : m_vec_controls)
        {
            if (strings_are_equal(action_->name(), action->name()))
            {
                return action_;
            }
        }
        m_vec_controls.push_back(action);
        return m_vec_controls.back();
    }
    void c_stage::enable_controls()
    {
        m_mutex.lock();
        {
            for (auto& action_ : m_vec_controls)
            {
                action_->enable();
            }
        }
        m_mutex.unlock();
    }
    void c_stage::disable_controls()
    {
        m_mutex.lock();
        {
            for (auto& action_ : m_vec_controls)
            {
                action_->disable();
            }
        }
        m_mutex.unlock();
    }
    void c_stage::run()
    {
        m_initial_action();
        m_initial_action_complete = true;
        enable_controls();
    }
    std::shared_ptr<c_stage> c_stage::make(std::wstring_view name, wstr_func_t& initial_action)
    {
        auto ptr = std::make_shared<c_stage>(name, initial_action);
        return ptr;
    }

    void c_pipeline::init()
    {
        m_thread_exists.store(true);
        m_thread = std::thread(std::bind(&c_pipeline::thread_function, this));
    }
    void c_pipeline::run()
    {
        m_run.store(true);
    }
    void c_pipeline::stop()
    {
        m_run.store(false);
    }
}



namespace owd
{
	c_pipeline* c_pipeline::m_singleton = nullptr;
	
	c_pipeline* owd::c_pipeline::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_pipeline();
		}

		return m_singleton;
	}
	
	void c_pipeline::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
            m_singleton->m_thread_exists.store(false);
            if (m_singleton->m_thread.joinable())
            {
                m_singleton->m_thread.join();
            }
			delete m_singleton;
			m_singleton = nullptr;
		}
	}
    void c_pipeline::enable_controls()
    {
        m_current_stage->enable_controls();
    }
    void c_pipeline::disable_controls()
    {
        m_current_stage->disable_controls();
    }
    stage_t& c_pipeline::add_stage(std::wstring_view name, wstr_func_t& initial_action)
    {
        auto stage = c_stage::make(name, initial_action);
        m_vec_stages.push_back(stage);

        return m_vec_stages.back();
    }
    stage_t& c_pipeline::get_stage(std::wstring_view name)
    {
        for (auto& stage : m_vec_stages)
        {
            if (strings_are_equal(stage->name(), name))
            {
                return stage;
            }
        }
        return m_current_stage;
    }
    stage_t& c_pipeline::set_stage(std::wstring_view name)
    {
        std::wcout << "Stage [" << name << "]\n";
 
        m_current_stage = get_stage(name);
        m_current_stage->reset();
        
        std::wcout << "Controls: \n";

        auto& vec_contr = c_controls::get_instance()->get();

        for (auto& c_ : vec_contr)
        {
            if (c_->is_enabled())
            {
                std::wcout << c_->name() << '\n';
            }
        }

        return m_current_stage;
    }
    void c_pipeline::thread_function()
    {
        while (true)
        {
            if (!m_thread_exists)
            {
                break;
            }
            // 1. Run initial action in current stage. 
            // If current stage has cotrols, activate controls of current stage. 
            // Controls are handled in another thread.
            if (m_run.load())
            {
                auto lock = std::lock_guard(m_mutex);
                if (!m_current_stage->initial_action_complete())
                {
                    m_current_stage->run();
                }
            }

            // 2. Current stage will be changed in initial action of the stage or in controls action.
            sleep_for_ms(1);
        }
    }
    c_pipeline::c_pipeline()
    {
    }
    c_pipeline::~c_pipeline()
    {
    }
}
