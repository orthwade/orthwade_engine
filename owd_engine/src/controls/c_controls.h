#pragma once
#include <functional>
#include <thread>
#include <memory>
#include <string>
#include <string_view>
#include <atomic>
#include <mutex>

#include <owd_lib.h>

namespace owd
{
	typedef std::function<std::wstring_view()> wstr_func_t;
	class c_action
	{
	public:
		c_action(int32_t _key_code, wstr_func_t& _action, std::wstring_view name);
		inline void set_action(wstr_func_t& action) { m_action = action; }
		inline bool is_enabled() { return m_enabled; }
		inline void enable() { m_enabled = true; }
		inline void disable() { m_enabled = false; }
		inline int32_t& key() { return m_key; }
		inline void do_() { m_action(); }
		inline std::wstring_view name() { return m_name; }
		static std::shared_ptr<c_action>& empty_action();
		static std::wstring_view empty_string();
		inline std::wstring_view next_stage() { return m_next_stage; }
	private:
		static std::wstring m_empty_string;
		std::wstring m_name{ L"" };
		std::wstring m_next_stage{ L"" };
		wstr_func_t m_action{};
		int32_t m_key = 0;
		std::atomic_bool m_enabled = false;
	};

	typedef std::shared_ptr<c_action> action_t;

	action_t& make_action(int32_t key_code, wstr_func_t& action, std::wstring_view name);

	class c_controls
	{
	public:
		action_t& add_action(int32_t key_code, wstr_func_t& action, std::wstring_view name);
		action_t& get_action(std::wstring_view name);
		action_t& last_action();

		std::vector<action_t>& get() { return m_vec_actions; }
		
		void init();

		void run();
		void stop();

		void disable_controls();

		static c_controls* get_instance();
		static void terminate();

	protected:
		std::vector<action_t> m_vec_actions{};

		std::thread m_thread{};

		std::atomic_bool m_thread_exists{ false };
		std::atomic_bool m_run{ false };

		std::mutex m_thread_mutex{};

		void thread_function();

		static c_controls* m_singleton;

		c_controls();
		~c_controls();
		
		c_controls(const c_controls&) = delete;
		c_controls& operator=(const c_controls&) = delete;
	};
}