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

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#elif defined SDL_BACKEND
#undef main
#endif

#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
// it is almost a neccesaty to create a context to pass all neccesary variables we create in main to the emscripten_main_loop
// to use lambda functions a kind of shit when you need to pass a c func-pointer...
yt2d::Window* window;
RenderTexture2D* test_render_texture;
Shader2D* screen_shader;
//Quad quad;
//Quad tr;
float ms = 0;

void main_loop(void *arg)//void *arg
{
    std::cout << "main_loop" << std::endl;
    window->pollEvent();
    
    /*
    //uint8_t ms = (uint8_t)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    //std::cout << ms / 256.0 << std::endl;
    // FIXME: there is smthng wrong with shaders!!!
    screen_shader->set<float, 2>("mouse_pos", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
    screen_shader->set<float>("time", ms);
    */
    
    //glViewport(200, 0, 800, 600);
    test_render_texture->bind();
        window->clear();
        //TODO: Render shader via a projection matrix to get a proper result from the scaling of vertices according to window size...
        // FIXME: there is smthng wrong with shaders!!!
        //tr.render(screen_shader);
    test_render_texture->unbind();
    
    
    //glViewport(0, 0, 1920, 1080);
    
    window->clear(0, 1, 1);
        //test_render_texture->get_texture()
        gui_draw(test_render_texture->get_texture(), screen_shader);
        
        //test_render_texture.bind_texture();
        //quad.render(&test_shader);
        //test_render_texture.unbind_texture();
    window->display();
    /*
    */
    
    std::cout << "Hello!" << std::endl;
}

int main()
{
    
    yt2d::Window swindow("SHADER EDITOR", 1920, 1080);
    window = &swindow;
    
    gui_start(*window);
    
    
    Texture2D test_texture_fbo;
    test_texture_fbo.create_texture(1920, 1080, NULL);
    test_render_texture = new RenderTexture2D(&test_texture_fbo);


    // FIXME: there is smthng wrong with shaders!!!
    /*
    glcompiler::init();
    Shader2D* screen_shader = new Shader2D();


    screen_shader->load_shader_code("../../shaders/notexture_frag.glsl", Shader2D::ShaderCodeType::FRAGMENT_SHADER);

    
    glcompiler::compile_and_attach_shaders(screen_shader);
    */
    

#ifdef __EMSCRIPTEN__
    // NOTE: using emscripten_set_main_loop_arg instead of emscripten_set_main_loop fixed every fucking problem!
    emscripten_set_main_loop_arg(main_loop, nullptr, -1, 1);
#elif defined SDL_BACKEND
    while(!window->isClose())
    {
        main_loop();
    }
#endif

    gui_destroy();
    //delete test_render_texture;
    /*
    */

    //delete window;

    return 0;
}

#else
int main()
{
    
    yt2d::Window window("SHADER EDITOR", 1920, 1080);
    gui_start(window);
    
    Texture2D test_texture_fbo(1920, 1080, NULL);
    //test_texture_fbo.create_texture(1920, 1080, NULL);
    RenderTexture2D test_render_texture(&test_texture_fbo);
    
    glcompiler::init();
    
    Shader2D* screen_shader = new Shader2D();

    Quad quad;
    Quad tr;

    screen_shader->load_shader_code("../../shaders/notexture_frag.glsl", Shader2D::ShaderCodeType::FRAGMENT_SHADER);
    
    ImGui::GetMousePos();
    

    
    glcompiler::compile_and_attach_shaders(screen_shader);
    
    
    /*
    screen_shader = new Shader2D();
    screen_shader->load_shader_code("../../shaders/notexture_frag.glsl", Shader2D::ShaderCodeType::FRAGMENT_SHADER);
    glcompiler::compile_and_attach_shaders(screen_shader);*/
    



//ImGui::Begin("hey");
//ImGui::Image(*test_render_texture.get_texture(), {200, 200});
//ImGui::End();

    auto main_loop = [&]()
    {
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
                
                //test_render_texture.bind_texture();
                //quad.render(&test_shader);
                //test_render_texture.unbind_texture();
            window.display();
            
        }
    };

    main_loop();
    
    
    delete screen_shader;
    gui_destroy();
    
    return 0;
}

#endif

//emscripten_set_main_loop(main_loop, 60, 0);