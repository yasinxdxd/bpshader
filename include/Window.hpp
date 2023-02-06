#ifndef YT2D_WINDOW_HPP
#define YT2D_WINDOW_HPP
#include <Definitions.hh>
#include <string>

struct GLFWwindow;
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
        operator GLFWwindow*()
        {
            return m_window;
        }

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
        GLFWwindow* m_window;
        u32 m_width;
        u32 m_height;
        std::string m_title;

    };
}

namespace _priv::callbacks
{
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
}

#endif//YT2D_WINDOW_HPP