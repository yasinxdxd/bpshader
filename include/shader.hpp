#ifndef Shader_HPP
#define Shader_HPP

#include <string>
#include <shader_compiler.hpp>

class Shader
{
public:
    enum class ShaderCodeType
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

public:
    Shader();
    Shader(const char* path, ShaderCodeType type = ShaderCodeType::FRAGMENT_SHADER);
    Shader(const Shader&) = delete; // non construction-copyable
    Shader& operator=(const Shader&) = delete; // non copyable
    ~Shader();

    _NORETURN_ void load_shader_code(const char* path, ShaderCodeType type = ShaderCodeType::FRAGMENT_SHADER);

    
    template <typename T, size_t _D = 1>
    _NORETURN_ void set(std::string name, T value) const;
    template <typename T, size_t _D = 2>
    _NORETURN_ void set(std::string name, T value1, T value2) const;

    operator unsigned int();

private:
    std::string* m_shader_vertex_code_text;
    std::string* m_shader_fragment_code_text;
    unsigned int m_gl_shader_program_id;
    bool m_use_default_vertex_shader = true;

    friend void glcompiler::compile_and_attach_shaders(Shader* shader);
    friend void glcompiler::save_shader_binary();
};

#endif//Shader_HPP
