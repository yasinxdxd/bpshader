#version 330 core

out vec4 result_frag_color;
in vec3 o_vertex_color;
in vec2 o_vertex_uv;

uniform float time;

void main()
{
    const int factor = 400;
    if(sin(o_vertex_uv.x * factor) > 0.5 || sin(o_vertex_uv.y * factor) > 0.5)
        result_frag_color = vec4(0.9, 0.9, 0.9, 1.0);
    else
        result_frag_color = vec4(sin(time) *  o_vertex_uv.x, 0.2, 0.2, 1.0);
};
