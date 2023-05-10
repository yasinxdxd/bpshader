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

void render(unsigned int& vertex_array_object, unsigned int vertex_size, Shader* shader, shader_function func)
{
    glUseProgram(*shader);

    if (func)
        func(shader);

    glBindVertexArray(vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, vertex_size);
    glBindVertexArray(0);//be sure that binded VAO is not changed by outside.
}

MeshStatic::MeshStatic()
{
    //vertex buffer object
    glGenBuffers(1, &m_gl_VBO);
    //vertex array object
    glGenVertexArrays(1, &m_gl_VAO);
}

MeshStatic::~MeshStatic()
{
    glDeleteBuffers(1, &m_gl_VBO);
    glDeleteVertexArrays(1, &m_gl_VAO);

    if (m_vertices)
        delete m_vertices;
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

        m_vertices = new float[curMesh.Vertices.size() * 8];
    
        size_t j = 0;
        for (size_t i = 0; i < curMesh.Vertices.size(); i++)
        {
            m_vertices[j + 0] = curMesh.Vertices[i].Position.X;
            m_vertices[j + 1] = curMesh.Vertices[i].Position.Y;
            m_vertices[j + 2] = curMesh.Vertices[i].Position.Z;
            m_vertices[j + 3] = curMesh.Vertices[i].Normal.X;
            m_vertices[j + 4] = curMesh.Vertices[i].Normal.Y;
            m_vertices[j + 5] = curMesh.Vertices[i].Normal.Z;
            m_vertices[j + 6] = curMesh.Vertices[i].TextureCoordinate.X;
            m_vertices[j + 7] = curMesh.Vertices[i].TextureCoordinate.Y;
            j += 8;
        }
            
        glBindBuffer(GL_ARRAY_BUFFER, m_gl_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

        glBindVertexArray(m_gl_VAO);

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
