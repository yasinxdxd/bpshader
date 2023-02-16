#version 430 core

out vec4 result_frag_color;
in vec3 o_vertex_color;
in vec2 o_vertex_uv;

void main()
{
    result_frag_color = vec4(o_vertex_uv.xy, 0.0, 1.0);
}