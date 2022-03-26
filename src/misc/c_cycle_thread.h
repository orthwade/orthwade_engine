#pragma once
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include "../debug/logger/logger.h"
#include "sleep_for/c_sleep_for.h"

namespace owd_lib
{
	class c_cycle_thread
	{
	public:
		c_cycle_thread();
		~c_cycle_thread();

		void assign_function(std::function<void()> func);

		void start();
		void pause();
		void stop();

		void set_period_mcs(uint64_t mcs);

		void set_name(std::wstring_view name);

	private:
		static constexpr std::atomic<uint16_t> thread_default = 0;
		static constexpr std::atomic<uint16_t> thread_started = 1;
		static constexpr std::atomic<uint16_t> thread_paused  = 2;
		static constexpr std::atomic<uint16_t> thread_stopped = 3;

		c_sleep_for_mcs m_sleep_mcs{};

		std::wstring m_name{};

		c_logger m_logger{ L"while_thread" };

		std::atomic<uint16_t> m_state = thread_default.load();

		std::function<void()> m_function = [&] {};

		std::thread m_thread{};

		std::recursive_mutex m_mtx{};
		std::mutex m_thread_mtx{};

		uint64_t m_period_mcs = 1000;

		void m_start_thread();

	};
}



