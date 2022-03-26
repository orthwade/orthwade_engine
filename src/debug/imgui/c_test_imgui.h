#pragma once
#include <functional>
#include "../c_ogl_debug.h"


// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include "../../graphics/opengl/glfw3.h" // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace owd_lib
{

	class c_imgui_slider
	{
	public:
		 c_imgui_slider(float& value, float min, float max, std::wstring_view name);
		~c_imgui_slider();

		void operator()();

	private:
		std::wstring m_name{};

		float m_min{};
		float m_max{};

		float* m_value_ptr = nullptr;

		bool m_enabled = true;

	};

	class c_imgui_checkbox
	{
	public:
		c_imgui_checkbox(bool& value, std::wstring_view name);
		~c_imgui_checkbox();

		void operator()();

	private:
		std::wstring m_name{};

		bool* m_value_ptr = nullptr;

		bool m_enabled = true;
	};

	template <typename T>
	class c_imgui_list
	{
	public:
		c_imgui_list(std::vector<T> vec_values, T& value_handle, std::vector<std::wstring_view> item_names,
			std::wstring_view name);
		~c_imgui_list();

		void operator()();
		//char const* const names_c_str();
	private:
		std::wstring m_name{};
		std::vector<std::string> m_vec_names{};
		std::vector<T> m_vec_values{};
		T* m_value_ptr = nullptr;
		int32_t m_value_int{};

		bool m_enabled = true;
	};

	template<typename T>
	owd_lib::c_imgui_list<T>::c_imgui_list
	(std::vector<T> vec_values, T& value_handle, std::vector<std::wstring_view> item_names,
		std::wstring_view name)
	{
		m_name = name;
		for (index_t i = 0; i != item_names.size(); ++i)
		{
			m_vec_names.push_back(c_convert_strings::utf_8(item_names[i]));
		}
		m_vec_values = vec_values;
		m_value_ptr = &value_handle;
	}

	template<typename T>
	c_imgui_list<T>::~c_imgui_list()
	{
	}
	template<typename T>
	void owd_lib::c_imgui_list<T>::operator()()
	{
		auto name_utf_8_string = c_convert_strings::utf_8(m_name);
		const char* label = name_utf_8_string.c_str();

		int32_t* current_item = &m_value_int;

		int32_t items_count = static_cast<int32_t>(m_vec_values.size());
		
		std::vector<char*> vec_c_str{};
		for (index_t i = 0; i != m_vec_names.size(); ++i)
		{
			vec_c_str.push_back(m_vec_names[i].data());
		}
		char** items = vec_c_str.data();

		

		for (index_t i = 0; i != m_vec_values.size(); ++i)
		{
			if (i == m_value_int)
			{
				*m_value_ptr = m_vec_values[i];
			}
		}
		ImGui::ListBox
		(label, current_item, items, items_count);
	}

	class c_test_imgui
	{
	public:
		c_test_imgui();
		~c_test_imgui();

		c_test_imgui(const c_test_imgui& other);
		c_test_imgui& operator=(const c_test_imgui& other);

		void set_name(std::wstring_view name);

		std::wstring_view name()
		{
			return m_name;
		}

		//bool add_slider(float &value, std::wstring_view name);

		void init(GLFWwindow* window);

		void terminate();

		void update_window();

		void set_font(const char* filename, float size = 30);

		void add_slider(float& value, float min, float max, std::wstring_view name);
		void add_checkbox(bool& value, std::wstring_view name);

		void add_listbox(std::vector<enm_log_mode> vec_values, enm_log_mode& value_handle, 
			std::vector<std::wstring_view> item_names,
			std::wstring_view name);

		bool enabled = true;

	private:
		std::wstring m_name{ L"c_test_imgui_object" };

		c_logger m_logger{ L"c_test_imgui" };

		std::mutex m_mtx{};

		const char* m_glsl_version = "#version 130";

		bool m_show_demo_window    = true;
		bool m_show_another_window = false;

		ImVec4 m_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		GLFWwindow* m_window = nullptr;

		float m_f = 0.0f;
		int m_counter = 0;

		std::vector<c_imgui_slider> m_vec_sliders{};
		std::vector<c_imgui_checkbox> m_vec_checkboxes{};
		std::vector<c_imgui_list<enm_log_mode>> m_vec_listboxes{};
	};

	
	

}