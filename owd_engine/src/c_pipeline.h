#pragma once
#include "controls/c_controls.h"

namespace owd
{
	class c_stage
	{
	public:
		c_stage(std::wstring_view name, wstr_func_t& initial_action);

		action_t& add_controls(int32_t key_code, wstr_func_t& action, std::wstring_view name);
		action_t& add_controls(action_t& action);

		inline std::wstring_view name() { return m_name; }
		inline std::wstring_view next_stage_name() { return m_next_stage_name; }

		void enable_controls();
		void disable_controls();

		void run();
		inline void reset() { m_initial_action_complete = false; }

		inline bool initial_action_complete() { return m_initial_action_complete; }

	private:
		static std::wstring m_empty_string;

		std::mutex m_mutex{};

		c_controls* m_controls = c_controls::get_instance();

		std::wstring m_name{ L"" };
		std::wstring m_next_stage_name{ L"" };

		wstr_func_t m_initial_action = []() { return m_empty_string; };
		bool m_initial_action_complete = false;
		std::vector<action_t> m_vec_controls{};
	};

	typedef std::shared_ptr<c_stage> stage_t;
	stage_t& make_stage(std::wstring_view name, wstr_func_t& initial_action);

	class c_pipeline
	{
	public:
		void init();
		void run();
		void stop();
		stage_t& add_stage(std::wstring_view name, wstr_func_t& initial_action);
		stage_t& get_stage(std::wstring_view name);

		stage_t& set_stage(std::wstring_view name);

	private:
		std::mutex m_mutex{};
		std::thread m_thread{};
		std::atomic_bool m_thread_exists{ false };
		std::atomic_bool m_run{ false };
		void thread_function();
		stage_t m_current_stage{};
		std::vector<stage_t> m_vec_stages{};

	public:
		static c_pipeline* get_instance();
		static void terminate();
	protected:
		static c_pipeline* m_singleton;

		c_pipeline();
		~c_pipeline();

		c_pipeline(const c_pipeline&) = delete;
		c_pipeline& operator=(const c_pipeline&) = delete;

	};
}