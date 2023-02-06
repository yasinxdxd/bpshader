#include <node_editor.hpp>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <ini.h>
#include <texture2d.hpp>
#include <shader2d.hpp>

#define IM_VEC2_CLASS_EXTRA \
ImVec2 ImVec2::operator+(ImVec2 right)\
{\
    return ImVec2(this->x + right.x, this->y + right.y);\
}

const auto global_map_func = [] (int value, int min1, int max1, int min2, int max2) -> float
{
    return min2 + (value - min1) * (float)(max2 - min2) / (float)(max1 - min1);
};

int my_round(float num)
{
    int int_num = (int)num;
    float frac = num - int_num;
    if(frac > 0.5f)
        return int_num + 1;
    
    return int_num;
}

#include <imgui.h>
#include <imnodes.h>

/*
    NODE_MAX_ATTRIBUTE içerisinde en fazla attribute barındıran node'un attribute sayısını belirler,
    her node farklı sayıda attribute barındırabileceğinden ötürü,
    node_index değerini bulurken id - last_id(yani attribute sayısı) faktörü göz önünde bulundurulmalıdır.
 */
#define NODE_MAX_ATTRIBUTE 6.0


extern glcompiler::_priv::_compiler_info compiler_info;

node_editor::MultiplyNode::MultiplyNode(const int i) : Node(i, Node::NodeType::MultiplyNode)
{
    this->inputs.resize(2);
    this->outputs.resize(1);
}

int node_editor::MultiplyNode::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Multiply (%d)", this->id);
    ImNodes::EndNodeTitleBar();
    
    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        ImGui::Text("in (%d)", this->id);
        ImNodes::EndInputAttribute();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        ImGui::Text("(%d)", this->id);
        ImGui::DragFloat("value", &this->inputs[i], 0.1f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    auto _sum = 1.0f;
    for(uint8_t t = 0; t < this->inputs.size(); t++)
    {
        _sum *= inputs[t];
    }
    outputs[0] = _sum;

    uint8_t j = 0;
    for(; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
        //this->outputs[j].second = this->id  + 2 + j + i;
        ImGui::Text("out (%d)", this->id);
        ImNodes::EndOutputAttribute();
    }
    
    ImNodes::EndNode();

    this->last_id = ++this->id;
    this->id = tmp_id;
    //printf("%d", this->last_id);
    return this->last_id;
}

node_editor::AdditionNode::AdditionNode(const int i) : Node(i, Node::NodeType::AdditionNode)
{
    this->inputs.resize(2);
    this->outputs.resize(1);
}

int node_editor::AdditionNode::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Addition (%d)", this->id);
    ImNodes::EndNodeTitleBar();
    
    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        //ImGui::TextUnformatted("in");
        ImGui::Text("in (%d)", this->id);
        //this->inputs[i].second = this->id + 1 + i;
        ImNodes::EndInputAttribute();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        ImGui::Text("(%d)", this->id);
        ImGui::DragFloat("value", &this->inputs[i], 0.1f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    auto _sum = 0.0f;
    for(uint8_t t = 0; t < this->inputs.size(); t++)
    {
        _sum += inputs[t];
    }
    outputs[0] = _sum;

    uint8_t j = 0;
    for(; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
        //this->outputs[j].second = this->id  + 2 + j + i;
        ImGui::Text("out (%d)", this->id);
        ImNodes::EndOutputAttribute();
    }
    
    ImNodes::EndNode();

    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

node_editor::FloatNode::FloatNode(const int i) : Node(i, Node::NodeType::FloatNode)
{
    memset(var_name, 0, 64);

    this->inputs.resize(1);
    this->outputs.resize(1);
}

int node_editor::FloatNode::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Float1 (%d)", this->id);
    ImNodes::EndNodeTitleBar();

    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        ImGui::Text("in (%d)", this->id);
        ImNodes::EndInputAttribute();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        ImGui::DragFloat("value", &this->inputs[i], 0.1f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    this->outputs[0] = this->inputs[0];

    uint8_t j = 0;
    for(; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
        ImGui::Text("out (%d)", this->id);
        ImNodes::EndOutputAttribute();
    }
    /*
    ImGui::PushItemWidth(120.0f);
    ImGui::InputText("name", var_name, 64);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();
    ImNodes::BeginStaticAttribute(this->id + 2);
    */
    
    ImNodes::EndNode();

    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

node_editor::BoolNode::BoolNode(const int i) : Node(i, Node::NodeType::BoolNode)
{
    this->inputs.resize(0);
    this->outputs.resize(1);
}

int node_editor::BoolNode::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);
    ImNodes::EndNode();
    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

node_editor::TimeNode::TimeNode(const int i) : Node(i, Node::NodeType::TimeNode)
{
    this->inputs.resize(0);
    this->outputs.resize(1);
}

int node_editor::TimeNode::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Time (%d)", this->id);
    ImNodes::EndNodeTitleBar();

    //Shader2D s;
    //s.set<float, 1>("time", t);
    // FIXME: add time constant to the shader as a uniform variable...
    this->outputs[0]++;

    for(uint8_t j = 0; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
        ImGui::Text("out (%d)", this->id);
        ImNodes::EndOutputAttribute();
    }

    ImNodes::EndNode();
    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

node_editor::ConditionNode::ConditionNode(const int i) : Node(i, Node::NodeType::ConditionNode)
{
    this->inputs.resize(2);
    this->outputs.resize(1);
}

int node_editor::ConditionNode::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);
    ImNodes::EndNode();
    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

#include <iostream>

void node_editor::Editor::show_editor()
{
    ImNodes::EditorContextSet(this->context);

    ImGui::Begin(window_name);
    ImGui::TextUnformatted("[Node Editor]");
    
    //When mouse is over the node editor side editor should be automatticly focused.
    if(ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImGui::GetWindowPos() + ImGui::GetWindowSize()))
        ImGui::SetWindowFocus(this->window_name);


    ImNodes::BeginNodeEditor();
    
    //TODO: add a right click menu on the node editor...
    //TODO: add a right click menu on the node editor...
    //TODO: add a right click menu on the node editor...

    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
        ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(ImGuiKey_A))
    {
        const int node_id = current_id;
        ImNodes::SetNodeScreenSpacePos(node_id, ImGui::GetMousePos());
        ImNodes::SnapNodeToGrid(node_id);

        switch (EditorManager::item_current_idx)
        {
        case node_editor::Node::NodeType::MultiplyNode:
            this->nodes.push_back(new MultiplyNode(node_id));
            break;
        case node_editor::Node::NodeType::AdditionNode:
            this->nodes.push_back(new AdditionNode(node_id));
            break;
        case node_editor::Node::NodeType::FloatNode:
            this->nodes.push_back(new FloatNode(node_id));
            break;
        case node_editor::Node::NodeType::BoolNode:
            this->nodes.push_back(new BoolNode(node_id));
            break;
        case node_editor::Node::NodeType::TimeNode:
            this->nodes.push_back(new TimeNode(node_id));
            break;
        case node_editor::Node::NodeType::ConditionNode:
            this->nodes.push_back(new ConditionNode(node_id));
            break;

        default:
            break;
        }
    }

    // delete nodes
    {  
        ImNodes::GetSelectedNodes(selected_node_ids);

        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
            ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(ImGuiKey_D))
            {
                // FIXME: do not allow user to delete more than one node.
                //for(size_t i = 0; selected_node_ids[0] != -1; i++)
                if( selected_node_ids[0] != -1)
                {
                    //Node* node_to_delete = get_node_by_id(selected_node_ids[0]);
                    //if(node_to_delete != nullptr)
                    {
                        /*
                        std::cout << global_map_func(selected_node_ids[0], 0, this->current_id, 0, this->nodes.size()) << std::endl;
                        auto node_index = my_round(
                        global_map_func(selected_node_ids[0], 0, this->current_id, 0, this->nodes.size())
                        * my_round((node_to_delete->id - node_to_delete->last_id) / NODE_MAX_ATTRIBUTE)
                        );
                        std::cout <<"map( "<< selected_node_ids[0] << ", "
                        << 0 << ", "
                        << this->current_id << ", "
                        << 0 << ", "
                        << this->nodes.size() << ") = "
                        << node_index << "\n";
                        
                        */
                        size_t node_index = get_node_index_by_id(selected_node_ids[0]);
                        for(size_t j = node_index + 1; j < this->nodes.size(); j++)
                        {
                            auto pos = ImNodes::GetNodeEditorSpacePos(this->nodes.at(j)->id);
                            this->nodes.at(j)->id -= (this->nodes.at(node_index)->last_id - this->nodes.at(node_index)->id);
                            ImNodes::SetNodeEditorSpacePos(this->nodes.at(j)->id, pos);
                        }
                        
                        this->nodes.erase(this->nodes.begin() + node_index);

                                                                    //i                    
                        ImNodes::ClearNodeSelection(selected_node_ids[0]);
                    }
                    

                    // FIXME: also fix the linkages after deletions.(delete linkages)
                }

                memset(selected_node_ids, -1, 64*sizeof(int));
            }
            

    }

    int _last_id = 0;
    for (size_t i = 0; i < this->nodes.size(); i++)
    {
        //printf_s("node data: %d", nodes[i]->id);
        _last_id = this->nodes[i]->show();
    }
    current_id = _last_id;

    for (const Link& link : this->links)
    {
        //printf_s("link data: %d, %d, %d", link.id, link.start_attr, link.end_attr);
        ImNodes::Link(link.id, link.start_attr, link.end_attr);
        Node *nb = nullptr, *ne = nullptr;
        
        //FIXME: set second as the index of the input/output pin??

        std::cout << link.id << std::endl;
        std::cout << "start : " << link.start_attr << std::endl;
        std::cout << "end   : " << link.end_attr << std::endl;

        for(const auto& node : nodes)
        {
            //std::cout << "thing : " << node->last_id << std::endl;
            if(link.start_attr > node->id && link.start_attr <= node->last_id)
            {
                nb = node;
            }
            if(link.end_attr > node->id && link.end_attr <= node->last_id)
            {
                ne = node;
            }
        }

        if(nb && ne)
        {
            const auto ne_in_size = ne->inputs.size();
            const auto nb_out_size = nb->outputs.size();
            auto ne_in_index = global_map_func(link.end_attr, ne->id, ne->last_id, 0, ne_in_size);
            auto nb_out_index = global_map_func(link.start_attr, nb->id, nb->last_id, 0, nb_out_size);

            printf("in_index  : %d\n", ne_in_index);
            printf("out_index : %d\n", nb_out_index);
            printf("nb: %d\n", nb->id);
            printf("ne: %d\n", ne->id);
            /*
            */
            ne->inputs[ne_in_index] = nb->outputs[nb_out_index];           
        }

        //TODO: add possibilities for float node or find a better way to implement linkages between Nodes...
    
    }

    ImNodes::EndNodeEditor();

    {
        //TODO: if the input and output types are match then allow to create a link othervise don't!
        Link link;
        if (ImNodes::IsLinkCreated(&link.start_attr, &link.end_attr))
        {
            link.id = current_link_id++;
            this->links.push_back(link);
            //printf("s:%d, e:%d\n", link.start_attr, link.end_attr);
        }
    }

    {
        int link_id;
        if (ImNodes::IsLinkDestroyed(&link_id))
        {
            auto iter = std::find_if(
                this->links.begin(), this->links.end(), [link_id](const Link& link) -> bool {
                    return link.id == link_id;
                });
            assert(iter != this->links.end());
            this->links.erase(iter);
        }
    }

    ImGui::End();
}

node_editor::Node* node_editor::Editor::get_node_by_id(uint64_t id) const
{
    for(auto* node : this->nodes)
    {
        if(node->id == id)
            return node;
    }

    return nullptr;
}

size_t node_editor::Editor::get_node_index_by_id(uint64_t id) const
{
    for(size_t i = 0; i < this->nodes.size(); i++)
    {
        if(this->nodes.at(i)->id == id)
            return i;
    }

    return -1;
}

void node_editor::Editor::initialize(const char* editor_name)
{
    strcpy(window_name, editor_name);
    this->context = ImNodes::EditorContextCreate();
    ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);

    ImNodesIO& io = ImNodes::GetIO();
    io.LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
    io.MultipleSelectModifier.Modifier = &ImGui::GetIO().KeyCtrl;

    ImNodesStyle& style = ImNodes::GetStyle();
    style.Flags |= ImNodesStyleFlags_GridLinesPrimary | ImNodesStyleFlags_GridSnapping;

    memset(selected_node_ids, -1, 64*sizeof(int));
}

void node_editor::Editor::shutdown()
{
    for (size_t i = 0; i < this->nodes.size(); i++)
        delete this->nodes[i];

    ImNodes::PopAttributeFlag();
    ImNodes::EditorContextFree(this->context);
}

void node_editor::Editor::save()
{
    // TODO: create your own .ini file ignore the imgui's and imnodes' ini files. Create them according to the node types and all neccessary informations
    // about nodes for interpreting that ini file into a real .glsl file 
    // that can be compiled as a (fragment(it has some global variables as vertex informations, time and mouse coordinates...)) shader.
    // FIXME:
    // Save the internal imnodes state
    ImNodes::SaveCurrentEditorStateToIniFile("save_load.ini");

    // Dump our editor state as bytes into a file
    // FIXME:
    std::fstream fout(
        "save_load.bytes", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

    const size_t num_nodes = this->nodes.size();
    const size_t num_links = this->links.size();
    fout.write(
        reinterpret_cast<const char*>(&num_nodes),
        static_cast<std::streamsize>(sizeof(size_t)));
    fout.write(
        reinterpret_cast<const char*>(&num_links),
        static_cast<std::streamsize>(sizeof(size_t)));
    
    // FIXME:
    /*
    for(size_t i = 0; i < num_nodes; i++)
    {
        fout.write(reinterpret_cast<const char*>(&this->nodes.at(0)->id), static_cast<std::streamsize>(sizeof(int)));
    }

    // FIXME:
    fout.write(
        reinterpret_cast<const char*>(this->links.data()),
        static_cast<std::streamsize>(sizeof(Link) * num_links));

        printf_s("sizeof(Node): %zd\n", sizeof(Node));
        printf_s("sizeof(Link): %zd\n", sizeof(Link));
    */

    //fout.write(reinterpret_cast<const char*>(&this->current_id), static_cast<std::streamsize>(sizeof(int)));
}

void node_editor::Editor::load()
{
    // Load the internal imnodes state
    // FIXME:
    /*
    mINI::INIFile ini_file("save_load.ini");
    mINI::INIStructure ini;
    ini_file.read(ini);
    */
    // FIXME:
    // FIXME:
    // FIXME:
    // Load our editor state into memory

    std::fstream fin("save_load.bytes", std::ios_base::in | std::ios_base::binary);

    if (!fin.is_open())
    {
        return;
    }

    try
    {
        size_t num_nodes;
        size_t num_links;
        fin.read(reinterpret_cast<char*>(&num_nodes), static_cast<std::streamsize>(sizeof(size_t)));
        fin.read(reinterpret_cast<char*>(&num_links), static_cast<std::streamsize>(sizeof(size_t)));
        
        // FIXME:
        for(static size_t i = 0; i < num_nodes; i++)
        {
            //const int node_id = get_id();
            /*
            std::string spos = ini["node." + std::to_string(node_id)]["origin"];
            
            std::stringstream ss(spos);  
            std::string nums;
            
            int iarr[2];
            unsigned short j = 0;
            while (std::getline(ss, nums, ','))  
            {
                iarr[j] = stoi(nums);
                j++;
            }
            
            ImVec2 vpos{static_cast<float>(iarr[0]),static_cast<float>(iarr[1])};
            printf_s("%f, %f\n", vpos.x, vpos.y);
            */

            //FIXME: set editor hovered and window focused...

            //ImNodes::SetNodeScreenSpacePos(node_id, vpos);
            //ImNodes::SnapNodeToGrid(node_id);
            //this->nodes.push_back(new MultiplyNode(this, node_id));
        }

        ImNodes::LoadCurrentEditorStateFromIniFile("save_load.ini");


        //this->links.resize(num_links);

        // FIXME:
        /*
        for(size_t i = 0; i < num_nodes; i++)
        {
            fin.read(reinterpret_cast<char*>(&this->nodes.at(0)->id), static_cast<std::streamsize>(sizeof(int)));
        }

        fin.read(
            reinterpret_cast<char*>(this->links.data()),
            static_cast<std::streamsize>(sizeof(Link) * num_links));
        */



        // copy current_id into memory
        //fin.read(reinterpret_cast<char*>(&this->current_id), static_cast<std::streamsize>(sizeof(int)));
    }
    catch(const std::exception& e)
    {
        printf_s("%s\n", e.what());
    }
    
    
}

void node_editor::EditorManager::show_node_list()
{
    ImGui::BeginChild(1, ImVec2{300, 800}, true);
    if (ImGui::BeginListBox("listbox 1", {300, 800}))
    {
        //ImGui::
        
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(items[n], is_selected))
                item_current_idx = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
    ImGui::EndChild();
}

void node_editor::EditorManager::show_shader_screen(Editor& editor, Texture2D*& texture, Shader2D*& shader)
{
    ImGui::BeginChild(2, ImVec2{820, 800}, true);
    ImGui::Image(*texture, {800, 600}, {-1, 1}, {0, 0});
        
        if(ImGui::Button("compile shader"))
        {
            delete shader;
            glcompiler::init();
            shader = new Shader2D();
            //shader->load_shader_code("../../shaders/test_vert.glsl", Shader2D::ShaderCodeType::VERTEX_SHADER);
            shader->load_shader_code("../../shaders/notexture_frag.glsl");
            glcompiler::compile_and_attach_shaders(shader);
        }

        if(ImGui::Button("save"))
        {
            editor.save();
        }
        if(ImGui::Button("load"))
        {
            editor.load();
        }

        ImGui::SetWindowFontScale(2.0);
        ImGui::TextColored({1.0, 0.0, 0.0, 1.0}, "%s", compiler_info.compile_log_info);
        ImGui::SetWindowFontScale(1.0);

    ImGui::EndChild();
    
}

void node_editor::EditorManager::show_shortcuts()
{
    ImGui::BeginChild("Shortcuts", ImVec2{300, 300},true);
    ImGui::TextColored(ImVec4(1, 0.81, 0.52, 1), "Press \'A\' to add new node.");
    ImGui::TextColored(ImVec4(1, 0.81, 0.52, 1), "Press \'D\' to delete selected node.");
    ImGui::EndChild();
}

