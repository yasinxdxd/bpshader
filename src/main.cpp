#include <shader.hpp>
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

#if defined __EMSCRIPTEN__
// it is almost a neccesaty to create a context to pass all neccesary variables we create in main to the emscripten_main_loop
// to use lambda functions a kind of shit when you need to pass a c func-pointer...
yt2d::Window* window;
RenderTexture2D* test_render_texture;
Shader* screen_shader;
Quad* quad;
Quad* tr;
float ms = 0;

void main_loop(void *arg)//void *arg
{
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

        render(*tr, 6, screen_shader);
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
    glcompiler::init();
    Shader* screen_shader = new Shader();

    tr = new Quad();

    screen_shader->load_shader_code("../../shaders/notexture_frag.glsl", Shader::ShaderCodeType::FRAGMENT_SHADER);

    
    glcompiler::compile_and_attach_shaders(screen_shader);
    /*
    */
    

#ifdef __EMSCRIPTEN__
    // NOTE: using emscripten_set_main_loop_arg instead of emscripten_set_main_loop fixed every fucking problem!
    emscripten_set_main_loop_arg(main_loop, nullptr, -1, 1);
#elif defined SDL_BACKEND
    while(!window->isClose())
    {
        main_loop(NULL);
    }
#endif

    gui_destroy();
    delete test_render_texture;
    delete tr;
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

    Texture2D renderer3d_texture_fbo(1920, 1080, NULL);
    RenderTexture2D renderer3d_render_texture(&renderer3d_texture_fbo);
    

    std::vector<Texture2D*> gui_textures(2);
    gui_textures[0] = test_render_texture.get_texture();
    gui_textures[1] = renderer3d_render_texture.get_texture();


    MeshStatic cube;
    cube.load_mesh("../../res/3d/box_stack.obj");
    
    Shader* renderer3d_shader = new Shader("../../shaders/3d_renderer_built_in_mesh_renderer_vert.glsl", Shader::ShaderCodeType::VERTEX_SHADER);
    renderer3d_shader->load_shader_code("../../shaders/3d_renderer_built_in_mesh_renderer_frag.glsl", Shader::ShaderCodeType::FRAGMENT_SHADER);


    glcompiler::init();


    
    Shader* screen_shader = new Shader();

    Quad quad;
    Quad tr;

    screen_shader->load_shader_code("../../shaders/notexture_frag.glsl", Shader::ShaderCodeType::FRAGMENT_SHADER);
    
    ImGui::GetMousePos();
    

    
    glcompiler::compile_and_attach_shaders(screen_shader);
    glcompiler::compile_and_attach_shaders(renderer3d_shader);
    
    
    /*
    screen_shader = new Shader();
    screen_shader->load_shader_code("../../shaders/notexture_frag.glsl", Shader::ShaderCodeType::FRAGMENT_SHADER);
    glcompiler::compile_and_attach_shaders(screen_shader);
    
    glm::mat4 view = glm::lookAt(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 proj = glm::perspective<float>(60.f, 8.f/6.f, 0.1, 100.f);
    glm::mat4 model = glm::identity<glm::mat4>();
*/


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
                render(tr, 6, screen_shader, nullptr);
            test_render_texture.unbind();


            renderer3d_render_texture.bind();
                window.clear();
                
                render(cube, 6, renderer3d_shader, [](Shader* shader) -> void 
                {
                    static float a = 0.1; 
                    glm::mat4 view = glm::lookAt(glm::vec3(0.f, 0.f, 2.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
                    glm::mat4 proj = glm::perspective<float>(60.f, 8.f/6.f, 0.01, 100.f);
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::rotate(model, a, glm::vec3(0.0, 1.0, 0.0));

                    std::cout << "shader func" << std::endl;

                    shader->set_matrix("m_model", model);
                    shader->set_matrix("m_view", view);
                    shader->set_matrix("m_projection", proj);

                    a += 0.01;

                });
            renderer3d_render_texture.unbind();
                
            
            //glViewport(0, 0, 1920, 1080);
            
            window.clear(1, 1, 1);
                gui_draw(gui_textures, screen_shader);
                
                //test_render_texture.bind_texture();
                //quad.render(&test_shader);
                //test_render_texture.unbind_texture();
            window.display();
            
        }
    };

    main_loop();
    
    
    delete screen_shader;
    delete renderer3d_shader;
    gui_destroy();
    
    return 0;
}

#endif

//emscripten_set_main_loop(main_loop, 60, 0);