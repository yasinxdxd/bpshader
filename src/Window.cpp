#include <Window.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <Vector.hh>

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
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void yt2d::Window::pollEvent(void)
{
    return glfwPollEvents();
}

void yt2d::Window::waitEvent(void)
{
    return glfwWaitEvents();
}

YT2D_NODISCARD bool yt2d::Window::isClose(void)
{
    return glfwWindowShouldClose(this->m_window);
}

void yt2d::Window::clear(void)
{
    glClearColor(0.0, 0.0, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor(0.9, 0.9, 0.9, 1);
}

void yt2d::Window::clear(float r, float g, float b)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(0.9, 0.9, 0.9, 1);
    glClearColor(r, g, b, 1);
}

void yt2d::Window::display(void)
{
    glfwSwapBuffers(m_window);
}

YT2D_NODISCARD YT2D_STATUS yt2d::Window::Init()
{
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
