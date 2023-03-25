#ifndef SHADER2D_HPP
#define SHADER2D_HPP

#include <string>
#include <shader_compiler.hpp>

class Shader2D
{
public:
    enum class ShaderCodeType
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

public:
    Shader2D();
    Shader2D(const char* path, ShaderCodeType type = ShaderCodeType::FRAGMENT_SHADER);
    Shader2D(const Shader2D&) = delete; // non construction-copyable
    Shader2D& operator=(const Shader2D&) = delete; // non copyable
    ~Shader2D();

    _NORETURN_ void load_shader_code(const char* path, ShaderCodeType type = ShaderCodeType::FRAGMENT_SHADER);

    
    template <typename T, size_t _D = 1>
    _NORETURN_ void set(std::string name, T value) const;
    template <typename T, size_t _D = 2>
    _NORETURN_ void set(std::string name, T value1, T value2) const;

    operator unsigned int();

private:
    std::string* m_shader2d_vertex_code_text;
    std::string* m_shader2d_fragment_code_text;
    unsigned int m_gl_shader2d_program_id;
    bool m_use_default_vertex_shader = true;

    friend void glcompiler::compile_and_attach_shaders(Shader2D* shader);
    friend void glcompiler::save_shader_binary();
};

#endif//SHADER2D_HPP
