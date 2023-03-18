#version 430

out vec4 result_frag_color;
in vec3 o_vertex_color;
in vec2 o_vertex_uv;

uniform sampler2D texture;

uniform vec2 mouse_pos;

//uniform float resolution;
vec2 resolution = vec2(800, 600);
vec2 mouse = vec2(mouse_pos.x/1920, mouse_pos.y/1080);
vec2 uv = o_vertex_uv;

//returns the state of the current texel + x,y. We just need the states "alive" or "dead".
//so we just return an integer 0 or 1
int get(float x, float y)
{
    return int(texture2D(texture, (uv.xy + vec2(x, y)/resolution)).b);
}

void main(void)
{
    //count the "living" neighbour texels
    int sum = get(-1, -1) +
              get(-1,  0) +
              get(-1,  1) +
              get( 0, -1) +
              get( 0,  1) +
              get( 1, -1) +
              get( 1,  0) +
              get( 1,  1);

    if (uv.x - 0.1 < mouse.x && uv.x + 0.1 > mouse.x
        &&
        uv.y - 0.1 < 1 - mouse.y && uv.y + 0.1 > 1 - mouse.y)
    {
        result_frag_color = vec4(1.0, 1.0, 1.0, 1.0);
    }

    //if we have 3 living neighbours the current cell will live, if there are two,
    //we keep the current state. Otherwise the cell is dead.
    if (sum==3)
    {
        result_frag_color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if (sum== 2)
    {
        float current = float(get(0, 0));
        result_frag_color = vec4(current, current, current, 1.0);
    }
/*
    else
    {
        result_frag_color = vec4(0.0, 0.0, 0.0, 1.0);
    }
    */
}