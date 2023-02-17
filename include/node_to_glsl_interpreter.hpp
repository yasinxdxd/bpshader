#ifndef NODE_TO_GLSL_INTERPRETER_HPP
#define NODE_TO_GLSL_INTERPRETER_HPP

// TODO: write an interpreter to create glsl code from your node editor...

// TODO: first write a .ini file that contains every possible information about nodes.
// TODO: then find a way to generate names without intersections.
// TODO: interprete the .ini file to generate glsl code.


#include <node_editor.hpp>
#include <fstream>

/*
TODO: fix the whole structure.
TODO: use a name_space
TODO: create lexer and parser functions/classes
FIXME: delete hard coded things...
*/

std::vector<std::string> interprete_result_color(node_editor::Editor& editor, const char* path)
{
    mINI::INIFile file(path);

    mINI::INIStructure ini;

    file.read(ini);

    // load size informations
    auto str_node_size = ini.get("size").get("node_size");
    const size_t node_size = std::stoi(str_node_size);

    // load node informations

    std::vector<std::string> rgba;

    for (size_t i = 0; i < node_size; i++)
    {
        auto str_node_index = std::to_string(i);
        auto str_node_id = ini.get("node" + str_node_index).get("node_id");
        auto str_node_type = ini.get("node" + str_node_index).get("node_type");

        int node_id = std::stoi(str_node_id);
        int node_type = std::stoi(str_node_type);
        
        if (static_cast<node_editor::Node::NodeType>(node_type) == node_editor::Node::NodeType::ResultColorNode)
        {
            for(size_t j = 0; j < 4; j++)
            {
                auto str_node_input_index = std::to_string(j);
                auto input = ini.get("node" + str_node_index).get("input" + str_node_input_index);
                rgba.push_back(input);
            }
            break;
        }

    }

    return rgba;
}

void generate_glsl(std::vector<std::string> rgba)
{
    /*
    result_frag_color = vec4(o_vertex_uv.xy, 0.0, 1.0);
    */
   std::string comma(",");
   std::string res = "result_frag_color = vec4(" + rgba.at(0) + comma + rgba.at(1) + comma + rgba.at(2) + comma + rgba.at(3) + std::string(");");

   std::string glsl = R"V0G0N(
    #version 430 core

    out vec4 result_frag_color;
    in vec3 o_vertex_color;
    in vec2 o_vertex_uv;

    void main()
    {
        
    }
)V0G0N";

    glsl.insert(140, res.c_str());
    std::cout << glsl << std::endl;

    std::fstream file("generated_fragemnt_shader.glsl", std::ofstream::out | std::ofstream::trunc);

    if (file.is_open())
    {
        file << glsl;
    }
    
    file.close();

}


#endif//NODE_TO_GLSL_INTERPRETER_HPP