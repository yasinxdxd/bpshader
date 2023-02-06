#ifndef GUI_HPP
#define GUI_HPP

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <imnodes.h>
#include <texture2d.hpp>
#include <Window.hpp>
#include <node_editor.hpp>
//#include <shader_compiler.hpp>
//#include <shader2d.hpp>

extern glcompiler::_priv::_compiler_info compiler_info;

ImFont *pfont_aldrich, *pfont_ubuntu;

static inline void InitIO()
{
    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig config;
    config.MergeMode = true;
    pfont_aldrich = io.Fonts->AddFontFromFileTTF("Aldrich-Regular.ttf", 16.0f);
    pfont_ubuntu = io.Fonts->AddFontFromFileTTF("Ubuntu-Title.ttf", 24.0f);//, &config, io.Fonts->GetGlyphRangesChineseFull()
}

#define _MY_IM_COLOR1 ImVec4(0.74f, 0.83f, 0.62f, 1.00f)
#define _MY_IM_COLOR2 ImVec4(0.74f, 0.83f, 0.62f, 1.00f)
#define _MY_IM_COLOR3 ImVec4(0.65f, 0.83f, 0.70f, 1.00f)

uint32_t vec4_2_uint(ImVec4 vec4)
{
    uint32_t a = 0;
    a += (uint8_t)(vec4.w*255);
    a <<= 24;
    uint32_t b = 0;
    b += (uint8_t)(vec4.z*255);
    b <<= 16;
    uint32_t g = 0;
    g += (uint8_t)(vec4.y*255);
    g <<= 8;
    uint32_t r = 0;
    r += (uint8_t)(vec4.x*255);


    return a+b+g+r;
}

static inline void InitStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    
#define IMSTYLE3
#include<imgui_styles.hxx>

}

#define INIT_IO InitIO();
#define INIT_STYLE InitStyle();

node_editor::Editor editor;
yt2d::Window* pwindow = nullptr;

void gui_start(yt2d::Window& window)
{
    IMGUI_CHECKVERSION();
    pwindow = &window;


    ImGui::CreateContext();
	ImNodes::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    INIT_IO
    INIT_STYLE

    editor.initialize("Node Editor");
}

void gui_draw(Texture2D* textures, Shader2D*& shader)
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();	

    // TODO: del ShowDemoWindow
    ImGui::PushFont(pfont_aldrich);
    //ImGui::ShowDemoWindow();
    

    
    ImGui::Begin("SHADER_EDITOR", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);// | ImGuiWindowFlags_DockNodeHost
    ImGui::SetWindowPos("SHADER_EDITOR", ImVec2{0, 0});
    ImGui::SetWindowSize("SHADER_EDITOR", ImVec2{(float)pwindow->getWindowWidth(), (float)pwindow->getWindowHeight()});   

        node_editor::EditorManager::show_node_list();
        ImGui::SameLine(320.0f);
        node_editor::EditorManager::show_shader_screen(editor, textures, shader);
        node_editor::EditorManager::show_shortcuts();
        
    ImGui::End();
    ImGui::PopFont();


    ImGui::PushFont(pfont_ubuntu);
    editor.show_editor();
    ImGui::PopFont();

	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void gui_destroy()
{
    editor.shutdown();
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImNodes::DestroyContext();
	ImGui::DestroyContext();
}


#endif//GUI_HPP