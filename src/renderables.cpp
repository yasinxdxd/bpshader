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

void render(unsigned int& vertex_array_object, unsigned int vertex_size, Shader* shader)
{
    glUseProgram(*shader);
    glBindVertexArray(vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, vertex_size);
    glBindVertexArray(0);//be sure that binded VAO is not changed by outside.
}

MeshStatic::MeshStatic()
{
}

MeshStatic::~MeshStatic()
{
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
		for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh curMesh = Loader.LoadedMeshes[i];
            //curMesh.Vertices[0].
		}	
	}
	else
	{
		// Output Error
		std::cerr << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";
	}
}
