#version 430 core

out vec4 result_frag_color;

in vec2 o_vertex_uv;
in vec3 o_vertex_normal;

uniform float time;

void main()
{
    result_frag_color = vec4(1.0, .5, 0.7, 1.0);
}