#include <Shader.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <defs.hh>
#include <glad/glad.h>
#include <stdarg.h>

//extern inline glshader_t _shader_DEFAULT_GL_VERTEX_SHADER;

Shader::Shader():
m_shader_fragment_code_text(nullptr),
m_shader_vertex_code_text(nullptr)
{

}

Shader::Shader(const char* path, ShaderCodeType type):
m_shader_fragment_code_text(nullptr),
m_shader_vertex_code_text(nullptr)
{
    load_shader_code(path, type);
}

Shader::~Shader()
{
    //we have deleted them inside the shader_compiler.cpp
    /*
    if(m_shader_fragment_code_text)
        delete m_shader_fragment_code_text;
    if(m_shader_vertex_code_text)
        delete m_shader_vertex_code_text;
    */
    glDeleteProgram(m_gl_shader_program_id);
}

_NORETURN_ void Shader::load_shader_code(const char* path, ShaderCodeType type)
{
    std::ifstream shader_file;   
    shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    std::string** shader_text_referance;

    if(type == ShaderCodeType::VERTEX_SHADER)
    {
        shader_text_referance = &m_shader_vertex_code_text;
        m_use_default_vertex_shader = false;
    }
    else
        shader_text_referance = &m_shader_fragment_code_text;
    
    try 
    {
        shader_file.open(path);

        if(shader_file.is_open())
        {
            std::stringstream Shader_sstream;
            // read file's buffer contents into stream
            Shader_sstream << shader_file.rdbuf();
            // close file handler
            shader_file.close();
            // convert stream into string
            if(*shader_text_referance == nullptr)
            {
                *shader_text_referance = new std::string(Shader_sstream.str());
            }
            else
            {
                delete shader_text_referance;
                *shader_text_referance = new std::string(Shader_sstream.str());
            }
        }
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << 
        e.what() << 
        std::endl;
    }
    
}

Shader::operator unsigned int()
{
    return m_gl_shader_program_id;
}

// FIXME: FIX the multi dimensional set methods with a better structure!!!

template <>
_NORETURN_ void Shader::set<int>(std::string name, int value) const
{
    glUseProgram(m_gl_shader_program_id);

    glUniform1i(
        glGetUniformLocation(m_gl_shader_program_id, name.c_str()),
        value);
}

template <>
_NORETURN_ void Shader::set<unsigned int>(std::string name, unsigned int value) const
{
    glUseProgram(m_gl_shader_program_id);

    glUniform1ui(
        glGetUniformLocation(m_gl_shader_program_id, name.c_str()),
        value);
}

template <>
_NORETURN_ void Shader::set<float>(std::string name, float value) const
{
    glUseProgram(m_gl_shader_program_id);

    glUniform1f(
        glGetUniformLocation(m_gl_shader_program_id, name.c_str()),
        value);
}

template <>
_NORETURN_ void Shader::set<double>(std::string name, double value) const
{
    glUseProgram(m_gl_shader_program_id);

    glUniform1d(
        glGetUniformLocation(m_gl_shader_program_id, name.c_str()),
        value);
}

template <>
_NORETURN_ void Shader::set<int, 2>(std::string name, int value) const
{
    int values[2];

    glUseProgram(m_gl_shader_program_id);

    glUniform2i(
        glGetUniformLocation(m_gl_shader_program_id, name.c_str()),
        values[0], values[1]);
}

template <>
_NORETURN_ void Shader::set<unsigned int, 2>(std::string name, unsigned int value) const
{
    unsigned int values[2];

    glUseProgram(m_gl_shader_program_id);

    glUniform2ui(
        glGetUniformLocation(m_gl_shader_program_id, name.c_str()),
        values[0], values[1]);
}

template <>
_NORETURN_ void Shader::set<float, 2>(std::string name, float value1, float value2) const
{
    float values[2];

    glUseProgram(m_gl_shader_program_id);

    glUniform2f(
        glGetUniformLocation(m_gl_shader_program_id, name.c_str()),
        value1, value2);
}

template <>
_NORETURN_ void Shader::set<double, 2>(std::string name, double value) const
{
    double values[2];
    
    glUseProgram(m_gl_shader_program_id);

    glUniform2d(
        glGetUniformLocation(m_gl_shader_program_id, name.c_str()),
        values[0], values[1]);
}
