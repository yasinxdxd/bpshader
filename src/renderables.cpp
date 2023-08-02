#define SHAPE_QUAD
#define SHAPE_TRIANGLE
#include <renderables.hpp>
#include <shader.hpp>
#include <glad/glad.h>

// model loading libs
#include <tiny_gltf_loader.h>
#include <OBJ_Loader.h>

Quad::Quad()
{
    //vertex array object
    glGenVertexArrays(1, &m_gl_VAO);
    glBindVertexArray(m_gl_VAO);
    
    //vertex buffer object
    glGenBuffers(1, &m_gl_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_gl_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
    
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "gl buffer error: " << error << std::endl;
    }

    //position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);

    //delete
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "vertex attrib pointer error: " << error << std::endl;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Quad::~Quad()
{
    glDeleteBuffers(1, &m_gl_VBO);
    glDeleteVertexArrays(1, &m_gl_VAO);
}

Triangle::Triangle()
{
    //vertex array object
    glGenVertexArrays(1, &m_gl_VAO);
    glBindVertexArray(m_gl_VAO);
    
    //vertex buffer object
    glGenBuffers(1, &m_gl_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_gl_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
    

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

void render(unsigned int& vertex_array_object, unsigned int size, Shader* shader, shader_function func, bool use_ebo)
{
    glUseProgram(*shader);
    std::cout << "rendering..." << std::endl;
    if (func)
        func(shader);

    glBindVertexArray(vertex_array_object);

    GLenum error;
    if(!use_ebo)
    {
        glDrawArrays(GL_TRIANGLES, 0, size);
        while ((error = glGetError()) != GL_NO_ERROR) {
            std::cout << "glDrawArrays error: " << error << std::endl;
        }
    }
    else
    {
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
        while ((error = glGetError()) != GL_NO_ERROR) {
            std::cout << "glDrawElements error: " << error << std::endl;
        }
    }
    glBindVertexArray(NULL);//be sure that binded VAO is not changed by outside.
    glUseProgram(NULL);

    
}

MeshStatic::MeshStatic()
{
    glGenVertexArrays(1, &m_gl_VAO);
    //vertex buffer object
    glGenBuffers(1, &m_gl_VBO);
    // FIXME: add index buffer and render mesh through indicies...
    glGenBuffers(1, &m_gl_EBO);
}

MeshStatic::~MeshStatic()
{
    glDeleteBuffers(1, &m_gl_VBO);
    glDeleteBuffers(1, &m_gl_EBO);
    glDeleteVertexArrays(1, &m_gl_VAO);

    if (m_vertices)
        delete[] m_vertices;
    if (m_indices)
        delete[] m_indices;
}

void MeshStatic::load_mesh(const char *path)
{
    // Initialize OBJ Loader
	objl::Loader Loader;

	// Load .obj File
	if (Loader.LoadFile(path))
	{
        std::cout << "meshes count: " << Loader.LoadedMeshes.size() << std::endl;
		// Go through each loaded mesh and out its contents
		
        objl::Mesh curMesh = Loader.LoadedMeshes[0];

        const size_t vertices_size = curMesh.Vertices.size() * 8;
        const size_t indices_size = curMesh.Indices.size();
        std::cout << curMesh.Vertices.size() << std::endl;

        m_vertices = new float[vertices_size];
        m_indices = new unsigned int[indices_size];
    
        size_t j = 0;
        for (size_t i = 0; i < curMesh.Vertices.size(); i++)
        {
            m_vertices[j + 0] = curMesh.Vertices[i].Position.X;
            m_vertices[j + 1] = curMesh.Vertices[i].Position.Y;
            m_vertices[j + 2] = curMesh.Vertices[i].Position.Z;
            m_vertices[j + 3] = curMesh.Vertices[i].TextureCoordinate.X;
            m_vertices[j + 4] = curMesh.Vertices[i].TextureCoordinate.Y;
            m_vertices[j + 5] = curMesh.Vertices[i].Normal.X;
            m_vertices[j + 6] = curMesh.Vertices[i].Normal.Y;
            m_vertices[j + 7] = curMesh.Vertices[i].Normal.Z;
            j += 8;
        }

        for (size_t i = 0; i < indices_size; i++)
        {
            m_indices[i] = curMesh.Indices.at(i);
            std::cout << m_indices[i] << " ";
        }
            
        glBindVertexArray(m_gl_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_gl_VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gl_EBO);

        glBufferData(GL_ARRAY_BUFFER, vertices_size, m_vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, m_indices, GL_STATIC_DRAW);

        //position data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5* sizeof(float)));
        glEnableVertexAttribArray(2);

        //delete
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

	}
	else
	{
		// Output Error
		std::cerr << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";
	}
}
