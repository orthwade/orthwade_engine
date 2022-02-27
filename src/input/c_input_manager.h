#pragma once
#include <stdint.h>
#include "../graphics/c_graphic_engine.h"

namespace owd
{
	void key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);

	enum class enm_key_state
	{
		press,
		release,
		idle
	};
	constexpr enm_key_state key_press	= enm_key_state::press;
	constexpr enm_key_state key_release = enm_key_state::release;
	constexpr enm_key_state key_idle = enm_key_state::idle;

	struct s_key
	{
		int32_t key{};
		enm_key_state state = key_idle;
	};

	class c_action
	{
	public:
		c_action(int32_t key_code, enm_key_state key_state, std::function<void()> action);

		inline void enable()  { m_enabled = true; }
		inline void disable() { m_enabled = false; }

		inline bool active() const { return m_enabled; }
		inline s_key& gey_key() { return m_key; }
		inline void do_() { m_action(); }
	private:
		bool m_enabled = false;
		s_key m_key{};
		std::function<void()> m_action{};

	};
	class c_input_manager
	{
	public:
		void add_action(int32_t key_code, enm_key_state key_state, std::function<void()> action);
		inline std::vector<c_action>& actions() { return m_actions; }
		inline std::vector<s_key>& keys() { return m_keys; }
		s_key& get_key(int32_t key_code);

		static c_input_manager* get_instance();
		static void terminate();

	protected:
		std::vector<s_key> m_keys{};
		std::vector<c_action> m_actions{};
		std::mutex m_thread_mutex{};
		std::atomic_bool m_thread_exists = true;
		std::thread m_thread{};
		void thread_function();
		static c_input_manager* m_singleton;

		c_input_manager();
		~c_input_manager();
		
		c_input_manager(const c_input_manager&) = delete;
		c_input_manager& operator=(const c_input_manager&) = delete;
	};
}