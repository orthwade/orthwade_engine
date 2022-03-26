#include "c_test_imgui.h"

namespace owd_lib
{
    c_test_imgui::c_test_imgui()
    {
        m_logger << "----c_test_imgui constructor START---- " << m_name << '\n';
        {

        }
        m_logger << "----c_test_imgui constructor OK---- " << m_name << '\n';
    }

   c_test_imgui::~c_test_imgui()
    {
       m_logger << "----c_test_imgui destructor START---- " << m_name << '\n';
       {

       }
       m_logger << "----c_test_imgui destructor OK---- " << m_name << '\n';
    }

    c_test_imgui::c_test_imgui(const c_test_imgui& other)
    {
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] START----\n";
        {
            *this = other;
        }
        m_logger << "----Copy construction from [" << other.m_name << "] of [" << m_name << "] OK----\n";
    }

    c_test_imgui& owd_lib::c_test_imgui::operator=(const c_test_imgui& other)
    {
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] START----\n";
        {
            if (this != &other)
            {
                m_name = other.m_name;
                m_logger = other.m_logger;
            }
        }
        m_logger << "----Assigning [" << other.m_name << "] to [" << m_name << "] OK----\n";
        return *this;
    }

    void c_test_imgui::set_name(std::wstring_view name)
    {
        m_logger << "----Setting name [" << name << "] to [" << m_name << "]----\n";
		{
			m_name = std::wstring(name);
		}
		m_logger << "----Setting name [" << name << "] to [" << m_name << "] OK----\n";
    }
    void c_test_imgui::init(GLFWwindow* window)
    {
        m_window = window;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.Fonts->AddFontDefault();
        //set_font("rsc/fonts/times.ttf");

        set_font("rsc/fonts/REFSAN.ttf", 18.0f);

        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
   //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

   // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();


        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init(m_glsl_version);

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);

    }
    void c_test_imgui::terminate()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    void c_test_imgui::update_window()
    {
        if (enabled)
        {

        }
        else
        {
            return;
        }
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        
        ////glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (m_show_demo_window)
        {
            ImGui::ShowDemoWindow(&m_show_demo_window);
        }

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Debug window");                            // Create a window called "Hello, world!" and append into it.
            
            //ImGui::Text("This is some useful text.");                 // Display some text (you can use a format strings too)
            //ImGui::Text(u8"Опер упал намоченный");                    // Display some text (you can use a format strings too)
            //ImGui::Checkbox("Demo Window", &m_show_demo_window);      // Edit bools storing our window open/close state
            //ImGui::Checkbox("Another Window", &m_show_another_window);

            //ImGui::SliderFloat("float", &m_f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
           // ImGui::ColorEdit3("clear color", (float*)&m_clear_color); // Edit 3 floats representing a color

            for (uint16_t i = 0; i != m_vec_sliders.size(); ++i)
            {
                m_vec_sliders[i]();
            }
            for (uint16_t i = 0; i != m_vec_checkboxes.size(); ++i)
            {
                m_vec_checkboxes[i]();
            }
            for (uint16_t i = 0; i != m_vec_checkboxes.size(); ++i)
            {
                m_vec_listboxes[i]();
            }
            //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            //    m_counter++;
            //ImGui::SameLine();
            //ImGui::Text("counter = %d", m_counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (m_show_another_window)
        {
            ImGui::Begin("Another Window", &m_show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                m_show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }
    void c_test_imgui::set_font(const char* filename, float size)
    {
        ImGuiIO& io = ImGui::GetIO();
        //ImGui::PopFont();
        io.Fonts->AddFontFromFileTTF(filename, size, 0, io.Fonts->GetGlyphRangesCyrillic());
    }
    void c_test_imgui::add_slider(float& value, float min, float max, std::wstring_view name)
    {
        m_vec_sliders.push_back({ value, min, max, name });
    }
    void c_test_imgui::add_checkbox(bool& value, std::wstring_view name)
    {
        m_vec_checkboxes.push_back({ value, name });
    }
    void owd_lib::c_test_imgui::add_listbox
    (std::vector<enm_log_mode> vec_values, enm_log_mode& value_handle, std::vector<std::wstring_view> item_names, 
        std::wstring_view name)
    {
        m_vec_listboxes.push_back({ vec_values, value_handle, item_names, name });
    }
    c_imgui_slider::c_imgui_slider(float& value, float min, float max, std::wstring_view name)
    {
        m_value_ptr = &value;

        m_min = min;
        m_max = max;

        m_name = name;
    }
    c_imgui_slider::~c_imgui_slider()
    {
    }
    void c_imgui_slider::operator()()
    {
        ImGui::SliderFloat(c_convert_strings::utf_8(m_name).c_str(), m_value_ptr, m_min, m_max);
    }
    c_imgui_checkbox::c_imgui_checkbox(bool& value, std::wstring_view name)
    {
        m_value_ptr = &value;

        m_name = name;
    }
    c_imgui_checkbox::~c_imgui_checkbox()
    {
    }
    void c_imgui_checkbox::operator()()
    {
        ImGui::Checkbox(c_convert_strings::utf_8(m_name).c_str(), m_value_ptr);
    }
}