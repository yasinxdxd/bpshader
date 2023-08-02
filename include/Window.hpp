#ifndef YT2D_WINDOW_HPP
#define YT2D_WINDOW_HPP
#include <Definitions.hh>
#include <string>

struct GLFWwindow;
#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
#include <SDL.h>
#endif

namespace ymath
{
    template <size_t _D, typename _Type>
    struct Vector;
}

namespace yt2d
{
    YT2D_CORE_CLASS Window
    {
    public:
        explicit Window(const std::string& title, u32 width, u32 height);
        explicit Window(const char* title, u32 width, u32 height);
        explicit Window(const std::string& title, ymath::Vector<2, float> size);
        explicit Window(const char* title, ymath::Vector<2, float> size);
        ~Window();
    
    public:
#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
        operator SDL_Window*()
        {
            return m_sdl_window;
        }
#else
        operator GLFWwindow*()
        {
            return m_window;
        }
#endif

        void pollEvent(void);
        void waitEvent(void);
        YT2D_NODISCARD bool isClose(void);
        void clear(void);
        void clear(float r, float g, float b);
        void display(void);

        u32 getWindowWidth();
        u32 getWindowHeight();

    private:
        YT2D_NODISCARD YT2D_STATUS Init();

    private:
        u32 m_width;
        u32 m_height;
        std::string m_title;

#if defined __EMSCRIPTEN__ || defined SDL_BACKEND
    private:
        SDL_Window* m_sdl_window;
        SDL_Event m_sdl_event;
        SDL_Renderer* m_sdl_renderer;
        SDL_GLContext m_sdl_gl_context;
        bool m_sdl_is_close = false;
    public:
        SDL_GLContext& getSDLGLContext() { return m_sdl_gl_context; }
#else
    private:
        GLFWwindow* m_window;
#endif

    };
}

namespace _priv::callbacks
{
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void glfw_error_callback(int error, const char* description);
    static void __stdcall gl_debug_callback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam);
}

#endif//YT2D_WINDOW_HPP