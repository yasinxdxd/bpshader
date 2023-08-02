#ifndef RENDERABLES_HPP
#define RENDERABLES_HPP

//#include <ve

#ifdef SHAPE_QUAD

class Shader;

struct Quad
{
    Quad();
    ~Quad();

    operator unsigned int&() { return m_gl_VAO; }

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

    operator unsigned int&() { return m_gl_VAO; }

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

// TODO: do something about mesh class and quads and triangles...


typedef void (*shader_function)(Shader*);
void render(unsigned int& vertex_array_object, unsigned int size, Shader* shader, shader_function func, bool use_ebo = false);


struct MeshStatic
{
    MeshStatic();
    ~MeshStatic();

    operator unsigned int&() { return m_gl_VAO; }

    void load_mesh(const char* path);

//private:
    float* m_vertices;
    unsigned int* m_indices;

    unsigned int m_gl_VBO;//vertex buffer object
    unsigned int m_gl_EBO;//index buffer object
    unsigned int m_gl_VAO;//vertex array object
};


#endif//RENDERABLES_HPP