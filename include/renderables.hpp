#ifndef RENDERABLES_HPP
#define RENDERABLES_HPP

#ifdef SHAPE_QUAD

class Shader2D;

struct Quad
{
    Quad();
    ~Quad();

    void render(Shader2D* shader);

private:
    float m_vertices[48] = {
    // positions          // colors           // texture coords
     1.f,  1.f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
     1.f, -1.f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
    -1.f, -1.f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -1.f, -1.f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -1.f,  1.f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   // top left 
     1.f,  1.f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
    };

    unsigned int m_gl_VBO;//vertex buffer object
    unsigned int m_gl_VAO;//vertex array object

};


#endif//SHAPE_QUAD

#ifdef SHAPE_TRIANGLE

struct Triangle
{
    Triangle();
    ~Triangle();

    void render(Shader2D* shader);

private:
    float m_vertices[36] = {
    // positions          // colors           // texture coords
    -1.f, -1.f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.f, -1.f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     0.0f, 1.f, 0.0f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    };

    unsigned int m_gl_VBO;//vertex buffer object
    unsigned int m_gl_VAO;//vertex array object
};
#endif//SHAPE_TRIANGLE



#endif//RENDERABLES_HPP