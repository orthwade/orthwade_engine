#include "c_cycle_thread.h"

namespace owd
{
	c_cycle_thread::c_cycle_thread()
	{
		m_logger << "----Cycle thread constructor START---- " << m_name << '\n';
		m_logger << "----Cycle thread constructor OK---- " << m_name << '\n';
	}

	c_cycle_thread::~c_cycle_thread()
	{
		m_logger << "----Cycle thread destructor START---- " << m_name << '\n';
		stop();
		m_logger << "----Cycle thread destructor OK---- " << m_name << '\n';
	}

	void c_cycle_thread::assign_function(std::function<void()> func)
	{
		//m_mtx.lock();
		{
			m_function = func;
		}
		//m_mtx.unlock();
	}

	void c_cycle_thread::start()
	{
		//m_mtx.lock();
		{
			m_logger << "Starting " << m_name << '\n';
			
			if (m_state == thread_stopped)
			{
				m_start_thread();
			}
			else if (m_state == thread_default)
			{
				m_start_thread();
			}
			else if (m_state == thread_started)
			{
				stop();
				m_start_thread();
			}
			else if (m_state == thread_paused)
			{
				
			}
			
			m_state = thread_started.load();
		}
		//m_mtx.unlock();
	}

	void c_cycle_thread::pause()
	{
		//m_mtx.lock();
		{
			m_logger << "Pausing " << m_name << '\n';
			m_state = thread_paused.load();

		}
		//m_mtx.unlock();
	}

	void c_cycle_thread::stop()
	{
		//m_mtx.lock();
		{
			m_logger << "Stopping " << m_name << '\n';
			if (m_state == thread_default)
			{
				m_logger << "Warning: thread is not started\n";
			}
			else if (m_state == thread_stopped)
			{
				m_logger << "Warning: thread is already stopped\n";
			}
			else
			{
				m_state = thread_stopped.load();
				m_thread.join();
			}
		}
		//m_mtx.unlock();
	}

	void c_cycle_thread::set_period_mcs(uint64_t mcs)
	{
		//m_mtx.lock();
		{
			m_logger << "Setting period: " << mcs << " microseconds\n";
			m_period_mcs = mcs;
		}
		//m_mtx.unlock();
	}
	void c_cycle_thread::set_name(std::wstring_view name)
	{
		//m_mtx.lock();
		{
			m_logger << "Setting name: " << name << '\n';
			m_name = std::wstring(name);
		}
		//m_mtx.unlock();
	}
	void c_cycle_thread::m_start_thread()
	{
		m_thread = std::thread
		([&]
			{
				while (true)
				{
					std::mutex m_thread_mtx{};
					m_thread_mtx.lock();
					{
						if (m_state == thread_stopped)
						{
							m_thread_mtx.unlock();
							break;
						}
						else if (m_state == thread_default)
						{
							//m_sleep_mcs(m_period_mcs);
						}
						else if (m_state == thread_started)
						{
							m_function();
							//m_sleep_mcs(m_period_mcs);
						}
						else if (m_state == thread_paused)
						{
							//m_sleep_mcs(m_period_mcs);
						}
						m_sleep_mcs(m_period_mcs);
					}
					m_thread_mtx.unlock();
				}
			}
		);
	}
}


