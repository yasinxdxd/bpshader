#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <defs.hh>

class Texture2D
{
public:
    Texture2D();
    Texture2D(const char* path);
    Texture2D(int width, int height, unsigned char* data);
    //Texture2D(const Texture2D&) = delete; // non construction-copyable
    //Texture2D& operator=(const Texture2D&) = delete; // non copyable
    ~Texture2D();

    bool load_texture(const char* path);
    _NORETURN_ void create_texture(int width, int height, unsigned char* data);
    _NORETURN_ void generate_texture();

    void bind();
    void unbind();

    operator unsigned char*() const;
    operator unsigned int*();
    operator unsigned int();
    operator void*();

private:
    unsigned char* m_texture2d_data;
    int m_texture2d_width,
    m_texture2d_height,
    m_texture2d_nmbrof_clr_chnnels;//number of color channels
    unsigned int m_gl_texture2d_texture_id;


friend class RenderTexture2D;
};

#endif//TEXTURE2D_HPP