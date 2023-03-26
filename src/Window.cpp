#include <Window.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <Vector.hh>
#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <imgui_impl_sdl.h>
#endif
#include <iostream>


yt2d::Window::Window(const std::string& title, u32 width, u32 height):
    m_title(title), m_width(width), m_height(height)
{
    auto a = Init();
}

yt2d::Window::Window(const char* title, u32 width, u32 height):
    m_title(title), m_width(width), m_height(height)
{
    auto a = Init();
}

yt2d::Window::Window(const std::string& title, ymath::Vec2f size):
    m_title(title), m_width(size.x), m_height(size.y)
{
    auto a = Init();
}

yt2d::Window::Window(const char* title, ymath::Vec2f size):
    m_title(title), m_width(size.x), m_height(size.y)
{
    auto a = Init();
}

yt2d::Window::~Window()
{
    
#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
    SDL_GL_DeleteContext(m_sdl_gl_context);
    SDL_DestroyWindow(m_sdl_window);
    SDL_DestroyRenderer(m_sdl_renderer);
	SDL_Quit();
#else
	glfwDestroyWindow(m_window);
    glfwTerminate();
#endif
}

void yt2d::Window::pollEvent(void)
{
#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
    while (SDL_PollEvent(&m_sdl_event))
	{
		// without it you won't have keyboard input and other things
		ImGui_ImplSDL2_ProcessEvent(&m_sdl_event);
		// you might also want to check io.WantCaptureMouse and io.WantCaptureKeyboard
		// before processing events

		switch (m_sdl_event.type)
		{
		case SDL_QUIT:
			m_sdl_is_close = true;
			break;

		case SDL_WINDOWEVENT:
			switch (m_sdl_event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch (m_sdl_event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_sdl_is_close = true;
				break;
			}
			break;
		}
	}
#else
    return glfwPollEvents();
#endif
}

void yt2d::Window::waitEvent(void)
{
#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
    /*...*/
#else
    return glfwWaitEvents();
#endif
}

YT2D_NODISCARD bool yt2d::Window::isClose(void)
{
#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
    return m_sdl_is_close;
#else
    return glfwWindowShouldClose(this->m_window);
#endif
}

void yt2d::Window::clear(void)
{
    glClearColor(0.0, 0.0, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //glClearColor(0.9, 0.9, 0.9, 1);
}

void yt2d::Window::clear(float r, float g, float b)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(0.9, 0.9, 0.9, 1);
    glClearColor(r, g, b, 1);
}

void yt2d::Window::display(void)
{
#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
    SDL_GL_SwapWindow(m_sdl_window);
#else
    glfwSwapBuffers(m_window);
#endif
}

YT2D_NODISCARD YT2D_STATUS yt2d::Window::Init()
{
#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
    SDL_Init(SDL_INIT_VIDEO);
    
	SDL_CreateWindowAndRenderer(m_width, m_height, SDL_WINDOW_OPENGL, &m_sdl_window, &m_sdl_renderer);
	
    SDL_SetWindowTitle(m_sdl_window, m_title.c_str());

	// imgui and gl thing
    
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	SDL_version compiled;
    SDL_VERSION(&compiled);

    SDL_version linked;
    SDL_GetVersion(&linked);

	//gl context
	m_sdl_gl_context = SDL_GL_CreateContext(m_sdl_window);
    
    if (m_sdl_gl_context == NULL)
    {
        SDL_GL_DeleteContext(m_sdl_gl_context);
        SDL_DestroyWindow(m_sdl_window);
	    SDL_DestroyRenderer(m_sdl_renderer);
        return YT2D_STATUS_ERROR;
    }
    SDL_GL_MakeCurrent(m_sdl_window, m_sdl_gl_context);
    
    // enable VSync
    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        return YT2D_STATUS_ERROR;
    }
    else
        std::cout << "[INFO] glad initialized" << std::endl;
#else
    //Init GLFW Library
    if(!glfwInit())
    {
        glfwTerminate();
        return YT2D_STATUS_ERROR;
    }

    //Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

    //Check window creation
    if(m_window == nullptr)
    {
        glfwTerminate();
        return YT2D_STATUS_ERROR;
    }

    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(m_window, _priv::callbacks::framebuffer_size_callback);
    
    //GLAD Library Init
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return YT2D_STATUS_ERROR;
    }
#endif



    return YT2D_STATUS_SUCCES;

}

void _priv::callbacks::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

u32 yt2d::Window::getWindowWidth()
{
    return m_width;
}

u32 yt2d::Window::getWindowHeight()
{
    return m_height;
}
