#version 430 core
layout (location = 0) in vec3 i_position; // the position variable has attribute position 0
layout (location = 1) in vec2 i_uv;
layout (location = 2) in vec3 i_normal;

  
out vec2 o_vertex_uv; // specify a color output to the fragment shader
out vec3 o_vertex_normal; // specify a color output to the fragment shader

// uniform variables
// MVP matricies
uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_projection;

vec4 calculate_3d_space(vec3 pos)
{
    vec4 result = m_projection * m_view * m_model * vec4(pos, 1.0);
    return result;
}

void main()
{
    gl_Position = calculate_3d_space(i_position);
    
    //send to fragment shader
    o_vertex_normal = i_normal;
    o_vertex_uv = i_uv;
}