#define SHAPE_QUAD
#define SHAPE_TRIANGLE
#include <renderables.hpp>
#include <shader2d.hpp>
#include <glad/glad.h>

Quad::Quad()
{
    //vertex buffer object
    glGenBuffers(1, &m_gl_VBO);
    //vertex array object
    glGenVertexArrays(1, &m_gl_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_gl_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(m_gl_VAO);

    //position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);

    //delete
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Quad::~Quad()
{
    glDeleteBuffers(1, &m_gl_VBO);
    glDeleteVertexArrays(1, &m_gl_VAO);
}

void Quad::render(Shader2D* shader)
{
    glUseProgram(*shader);
    glBindVertexArray(m_gl_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);//be sure that binded VAO is not changed by outside.
}

Triangle::Triangle()
{
    //vertex buffer object
    glGenBuffers(1, &m_gl_VBO);
    //vertex array object
    glGenVertexArrays(1, &m_gl_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_gl_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(m_gl_VAO);

    //position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);

    //delete
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Triangle::~Triangle()
{
    glDeleteBuffers(1, &m_gl_VBO);
    glDeleteVertexArrays(1, &m_gl_VAO);
}

void Triangle::render(Shader2D* shader)
{
    glUseProgram(*shader);
    glBindVertexArray(m_gl_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);//be sure that binded VAO is not changed by outside.
}