#define STB_IMAGE_IMPLEMENTATION
#include <texture2d.hpp>
#include <stb_image.h>
#include <defs.hh>
#include <glad/glad.h>
#include <stdio.h>

Texture2D::Texture2D(): m_texture2d_data(nullptr)
{

}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_gl_texture2d_texture_id);
    stbi_image_free(m_texture2d_data);
}

bool Texture2D::load_texture(const char* path)
{
    m_texture2d_data = stbi_load(path, &m_texture2d_width, &m_texture2d_height, &m_texture2d_nmbrof_clr_chnnels, 0);
    
    if(m_texture2d_data == nullptr)
        return false;
    
    return true;
}

void Texture2D::create_texture(int width, int height, unsigned char* data)
{
    m_texture2d_data = NULL;
    m_texture2d_width = width;
    m_texture2d_height = height;
    m_texture2d_nmbrof_clr_chnnels = 3;
}

_NORETURN_ void Texture2D::generate_texture()
{
    //create and bind texture id
    glGenTextures(1, &m_gl_texture2d_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_gl_texture2d_texture_id);

    //parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_LINEAR_MIPMAP_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //generate mipmap
    switch (m_texture2d_nmbrof_clr_chnnels)
    {
    case 3:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_texture2d_width, m_texture2d_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_texture2d_data);
        break;
    case 4:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texture2d_width, m_texture2d_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texture2d_data);
        break;
    default:
        break;
    }
    
    //glGenerateMipmap(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_gl_texture2d_texture_id);
}

void Texture2D::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::operator unsigned char*() const
{
    return m_texture2d_data;
}

Texture2D::operator unsigned int*()
{
    return &m_gl_texture2d_texture_id;
}

Texture2D::operator unsigned int()
{
    return m_gl_texture2d_texture_id;
}

Texture2D::operator void*()
{
    return reinterpret_cast<void*>(static_cast<unsigned __int64>(m_gl_texture2d_texture_id));
    //first we cast it int 64 to make the size 8 byte the same size with void*, then cast it void*
}
