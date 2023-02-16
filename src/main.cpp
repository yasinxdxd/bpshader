#include <shader2d.hpp>
#define SHAPE_QUAD
#define SHAPE_TRIANGLE
#include <renderables.hpp>
#include <gui.hpp>
#include <render_texture2d.hpp>
#include <glad/glad.h>

#include <iostream>
#include <chrono>
using namespace std::chrono;


int main()
{

    yt2d::Window window("SHADER EDITOR", 1920, 1080);
    gui_start(window);

    Texture2D test_texture_fbo;
    test_texture_fbo.create_texture(1920, 1080, NULL);
    RenderTexture2D test_render_texture(&test_texture_fbo);
    
    Shader2D* screen_shader = new Shader2D();
    Quad quad;
    Quad tr;
    
    screen_shader->load_shader_code("../../shaders/notexture_frag.glsl", Shader2D::ShaderCodeType::FRAGMENT_SHADER);
    
    ImGui::GetMousePos();
    

    glcompiler::init();
    glcompiler::compile_and_attach_shaders(screen_shader);
    
    screen_shader = new Shader2D();
    screen_shader->load_shader_code("../../shaders/notexture_frag.glsl", Shader2D::ShaderCodeType::FRAGMENT_SHADER);
    glcompiler::compile_and_attach_shaders(screen_shader);
    


/*
ImGui::Begin("hey");
ImGui::Image(*test_render_texture.get_texture(), {200, 200});
ImGui::End();
*/

    float ms = 0;
    while(!window.isClose())
    {
        window.pollEvent();
        ms++;
        //uint8_t ms = (uint8_t)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        //std::cout << ms / 256.0 << std::endl;
        screen_shader->set<float, 2>("mouse_pos", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
        screen_shader->set<float>("time", ms);

        //glViewport(200, 0, 800, 600);
        test_render_texture.bind();
            window.clear();
            //TODO: Render shader via a projection matrix to get a proper result from the scaling of vertices according to window size...
            tr.render(screen_shader);
        test_render_texture.unbind();
            
        
        //glViewport(0, 0, 1920, 1080);
        
        window.clear(1, 1, 1);
            gui_draw(test_render_texture.get_texture(), screen_shader);
            /*
            test_render_texture.bind_texture();
            quad.render(&test_shader);
            test_render_texture.unbind_texture();
            */
        window.display();
        
    }
    
    delete screen_shader;
    gui_destroy();
    
    return 0;
}