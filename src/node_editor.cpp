#include <node_editor.hpp>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <ini.h>
#include <texture2d.hpp>
#include <shader2d.hpp>
#include <iostream>
#include <defs.hh>
#include <node_to_glsl_interpreter.hpp>

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

#include <imconfig.h>
#include <imgui.h>
#include <imnodes.h>
#include <imgui_internal.h>
#include <ImGuiFileDialog.h>

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
    ImGui::Text("Multiply");
    ImNodes::EndNodeTitleBar();
    
    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        ImGui::Text("in");
        ImNodes::EndInputAttribute();

        ImGui::SameLine();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        //ImGui::Text("(%d)", this->id);
        ImGui::DragFloat("##value", &this->inputs[i], 0.1f);
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
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        //this->outputs[j].second = this->id  + 2 + j + i;
        ImGui::Text("out");
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
    ImGui::Text("Addition");
    ImNodes::EndNodeTitleBar();
    
    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        //ImGui::TextUnformatted("in");
        ImGui::Text("in");
        //this->inputs[i].second = this->id + 1 + i;
        ImNodes::EndInputAttribute();

        ImGui::SameLine();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        //ImGui::Text("(%d)", this->id);
        ImGui::DragFloat("##value", &this->inputs[i], 0.1f);
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
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        //this->outputs[j].second = this->id  + 2 + j + i;
        ImGui::Text("out");
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
    ImGui::Text("Float1");
    ImNodes::EndNodeTitleBar();

    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        ImGui::Text("in");
        ImNodes::EndInputAttribute();

        ImGui::SameLine();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        ImGui::DragFloat("##value", &this->inputs[i], 0.1f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    this->outputs[0] = this->inputs[0];

    uint8_t j = 0;
    for(; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        ImGui::Text("out");
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
    this->inputs.resize(1);
    this->outputs.resize(1);
}

int node_editor::BoolNode::show()
{
    const int tmp_id = this->id;

    ImNodes::BeginNode(this->id);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Bool");
    ImNodes::EndNodeTitleBar();


    ImNodes::EndNode();

    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

node_editor::Vec2Node::Vec2Node(const int i) : Node(i, Node::NodeType::Vec2Node)
{
    this->inputs.resize(2);
    this->outputs.resize(1);
}

int node_editor::Vec2Node::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);
    
    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Vec2");
    ImNodes::EndNodeTitleBar();

    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        ImGui::Text("in");
        ImNodes::EndInputAttribute();

        ImGui::SameLine();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        ImGui::DragFloat("##value", &this->inputs[i], 0.1f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    for(uint8_t j = 0; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        ImGui::Text("out");
        ImNodes::EndOutputAttribute();
    }

    ImNodes::EndNode();
    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

node_editor::Vec3Node::Vec3Node(const int i) : Node(i, Node::NodeType::Vec3Node)
{
    this->inputs.resize(2);
    this->outputs.resize(1);
}

int node_editor::Vec3Node::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);
    
    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Vec3");
    ImNodes::EndNodeTitleBar();

    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        ImGui::Text("in");
        ImNodes::EndInputAttribute();

        ImGui::SameLine();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        ImGui::DragFloat("##value", &this->inputs[i], 0.1f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    for(uint8_t j = 0; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        ImGui::Text("out");
        ImNodes::EndOutputAttribute();
    }

    ImNodes::EndNode();
    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

node_editor::Vec4Node::Vec4Node(const int i) : Node(i, Node::NodeType::Vec4Node)
{
    this->inputs.resize(2);
    this->outputs.resize(1);
}

int node_editor::Vec4Node::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);
    
    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Vec4");
    ImNodes::EndNodeTitleBar();

    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        ImGui::Text("in");
        ImNodes::EndInputAttribute();

        ImGui::SameLine();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        ImGui::DragFloat("##value", &this->inputs[i], 0.1f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    for(uint8_t j = 0; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        ImGui::Text("out");
        ImNodes::EndOutputAttribute();
    }

    ImNodes::EndNode();
    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

node_editor::ResultColorNode::ResultColorNode(const int i) : Node(i, Node::NodeType::ResultColorNode)
{
    this->inputs.resize(4);
    this->outputs.resize(1);
}

node_editor::ResultColorNode::~ResultColorNode()
{
    if (s_instance)
        delete s_instance;
}

node_editor::ResultColorNode* node_editor::ResultColorNode::get_instance(const int id)
{
    return s_instance == nullptr ? new ResultColorNode(id) : s_instance;
}

int node_editor::ResultColorNode::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);
    
    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Vec4");
    ImNodes::EndNodeTitleBar();

    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        ImGui::Text("in");
        ImNodes::EndInputAttribute();

        ImGui::SameLine();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        ImGui::DragFloat("##value", &this->inputs[i], 0.1f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }

    for(uint8_t j = 0; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        ImGui::Text("out");
        ImNodes::EndOutputAttribute();
    }

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
    ImGui::Text("Time");
    ImNodes::EndNodeTitleBar();

    //Shader2D s;
    //s.set<float, 1>("time", t);
    this->outputs[0]++;

    for(uint8_t j = 0; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        ImGui::Text("out");
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

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Condition");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(++this->id);
    //ImGui::TextUnformatted("in");
    ImGui::Text("in");
    //this->inputs[i].second = this->id + 1 + i;
    ImNodes::EndInputAttribute();
    
    ImGui::SameLine();

    ImNodes::BeginStaticAttribute(++this->id);
    ImGui::PushItemWidth(120.0f);
    //ImGui::Text("(%d)", this->id);
    ImGui::DragFloat("##value", &this->inputs[0], 0.1f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginStaticAttribute(++this->id);    
    ImGui::PushItemWidth(120.0f);

    float w = ImGui::CalcItemWidth();
    float spacing = 2;//style.ItemInnerSpacing.x;
    float button_sz = ImGui::GetFrameHeight();
    ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);
    if (ImGui::BeginCombo("##custom combo", current_item, ImGuiComboFlags_NoArrowButton))
    {
        ImGui::EndCombo();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##l", ImGuiDir_Left))
    {
        item_index--;
        current_item = items[item_index % IM_ARRAYSIZE(items)];
    }
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##r", ImGuiDir_Right))
    {
        item_index++;
        current_item = items[item_index % IM_ARRAYSIZE(items)];
    }

    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();


    ImNodes::BeginInputAttribute(++this->id);
    //ImGui::TextUnformatted("in");
    ImGui::Text("in");
    //this->inputs[i].second = this->id + 1 + i;
    ImNodes::EndInputAttribute();

    ImGui::SameLine();

    ImNodes::BeginStaticAttribute(++this->id);
    ImGui::PushItemWidth(120.0f);
    //ImGui::Text("(%d)", this->id);
    ImGui::DragFloat("##value", &this->inputs[1], 0.1f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    

    uint8_t j = 0;
    for(; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        //this->outputs[j].second = this->id  + 2 + j + i;
        ImGui::Text("out");
        ImNodes::EndOutputAttribute();
    }



    ImNodes::EndNode();
    
    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

node_editor::SinFunctionNode::SinFunctionNode(const int i) : Node(i, Node::NodeType::ConditionNode)
{
    this->inputs.resize(1);
    this->outputs.resize(1);
}

int node_editor::SinFunctionNode::show()
{
    const int tmp_id = this->id;
    ImNodes::BeginNode(this->id);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Sin");
    ImNodes::EndNodeTitleBar();

    uint8_t i = 0;
    for(; i < this->inputs.size(); i++)
    {
        ImNodes::BeginInputAttribute(++this->id);
        ImGui::Text("in");
        ImNodes::EndInputAttribute();

        ImGui::SameLine();

        ImNodes::BeginStaticAttribute(++this->id);
        ImGui::PushItemWidth(120.0f);
        ImGui::DragFloat("##value", &this->inputs[i], 0.1f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
    }


    ImNodes::BeginStaticAttribute(++this->id);    
    ImGui::PushItemWidth(120.0f);

    float w = ImGui::CalcItemWidth();
    float spacing = 2;//style.ItemInnerSpacing.x;
    float button_sz = ImGui::GetFrameHeight();
    ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);
    if (ImGui::BeginCombo("##custom combo", current_item, ImGuiComboFlags_NoArrowButton))
    {
        ImGui::EndCombo();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##l", ImGuiDir_Left))
    {
        item_index--;
        current_item = items[item_index % IM_ARRAYSIZE(items)];
    }
    ImGui::SameLine(0, spacing);
    if (ImGui::ArrowButton("##r", ImGuiDir_Right))
    {
        item_index++;
        current_item = items[item_index % IM_ARRAYSIZE(items)];
    }

    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();


    if(item_index % IM_ARRAYSIZE(items) == 0) // radian
        this->outputs[0] = sinf(this->inputs[0]);
    else                                      // degree
        this->outputs[0] = sinf(DEG2RAD(this->inputs[0]));


    uint8_t j = 0;
    for(; j < this->outputs.size(); j++)
    {
        ImNodes::BeginOutputAttribute(++this->id);
        const float text_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(120.f + ImGui::CalcTextSize("##value").x - text_width);
        ImGui::Text("out");
        ImNodes::EndOutputAttribute();
    }
    
    ImNodes::EndNode();

    this->last_id = ++this->id;
    this->id = tmp_id;
    return this->last_id;
}

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
    if (ImGui::GetIO().MouseClicked[1])
    {
        right_click_menu = true;
    }
    //TODO: add a right click menu on the node editor...
    //TODO: add a right click menu on the node editor...

    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
        ImNodes::IsEditorHovered() && (ImGui::IsKeyReleased(ImGuiKey_A)))
    {
        create_node(current_id, static_cast<Node::NodeType>(EditorManager::item_current_idx), ImGui::GetMousePos());
    }

    // delete nodes
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
        ImNodes::IsEditorHovered() && (ImGui::IsKeyReleased(ImGuiKey_D)))
    {
        ImNodes::GetSelectedNodes(selected_node_ids);
        delete_node(selected_node_ids[0]);
        memset(selected_node_ids, -1, 64*sizeof(int));
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
        /*
        std::cout << link.id << std::endl;
        std::cout << "start : " << link.start_attr << std::endl;
        std::cout << "end   : " << link.end_attr << std::endl;
        */

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

            /*
            printf("in_index  : %d\n", ne_in_index);
            printf("out_index : %d\n", nb_out_index);
            printf("nb: %d\n", nb->id);
            printf("ne: %d\n", ne->id);
            */
            ne->inputs[ne_in_index] = nb->outputs[nb_out_index];           
        }

        //TODO: add possibilities for float node or find a better way to implement linkages between Nodes...
    
    }


    // ImNodes readme.md says that it must be called right before EndNodeEditor
    ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight);

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

size_t node_editor::Editor::get_link_index_by_id(uint64_t id) const
{
    for(size_t i = 0; i < this->links.size(); i++)
    {
        if(this->links.at(i).id == id)
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
    // FIXME:
    // Save the internal imnodes state
    if (ImGui::Button("save node editor state"))
    {
        // TODO: add some popup menu to give a name to the saved file...
        mINI::INIFile nodeeditor_save_file("node_editor_save_file.ini");

        mINI::INIStructure ini;

        // save size informations
        auto str_node_size = std::to_string(this->nodes.size());
        auto str_link_size = std::to_string(this->links.size());
        ini["size"]["node_size"] = str_node_size;
        ini["size"]["link_size"] = str_link_size;

        // save node informations
        for (size_t i = 0; i < this->nodes.size(); i++)
        {
            auto str_node_index = std::to_string(i); 
            auto str_node_id = std::to_string(this->nodes[i]->id);
            auto str_node_type = std::to_string(this->nodes[i]->type);
            auto vec_node_pos = ImNodes::GetNodeScreenSpacePos(this->nodes[i]->id);
            auto str_node_pos_x = std::to_string(vec_node_pos.x);
            auto str_node_pos_y = std::to_string(vec_node_pos.y);
            ini["node" + str_node_index]["node_id"] = str_node_id;
            ini["node" + str_node_index]["node_type"] = str_node_type;
            for (size_t j = 0; j < this->nodes[i]->inputs.size(); j++)
            {
                auto str_node_input_index = std::to_string(j);
                auto str_node_input_value = std::to_string(this->nodes[i]->inputs[j]);
                ini["node" + str_node_index]["input" + str_node_input_index] = str_node_input_value; 
            }
            ini["node" + str_node_index]["node_pos_x"] = str_node_pos_x;
            ini["node" + str_node_index]["node_pos_y"] = str_node_pos_y;
        }

        // save link informations
        for (size_t i = 0; i < this->links.size(); i++)
        {
            auto str_link_index = std::to_string(i); 
            auto str_link_id = std::to_string(this->links[i].id);
            auto str_link_end_attr = std::to_string(this->links[i].end_attr);
            auto str_link_start_attr = std::to_string(this->links[i].start_attr);
            
            ini["link" + str_link_index]["link_id"] = str_link_id;
            ini["link" + str_link_index]["link_end"] = str_link_end_attr;
            ini["link" + str_link_index]["link_start"] = str_link_start_attr;
        }
        
        // @param true, pretty print(add white spaces)
        nodeeditor_save_file.generate(ini, true);

    }
    
    // Dump our editor state as bytes into a file
    // FIXME:
    
}

void node_editor::Editor::load()
{

    // TODO: ImGuiFileDialog::Instance() do not use that instead create instance variables...
    // and also use file dialog here too.

    // FIXME: right now it just read one file which is named "node_editor_save_file.ini" it will be changed

    if (ImGui::Button("load node editor state"))
    {

        // first erase all the nodes and links
        const size_t current_node_size = this->nodes.size();
        for (size_t i = 0; i < current_node_size; i++)
        {
            delete_node(this->nodes.at(current_node_size - i - 1)->id);
        }
        /**/
        
        mINI::INIFile file("node_editor_save_file.ini");

        mINI::INIStructure ini;

        file.read(ini);
        
        // read value safely - if key or section don't exist they will NOT be created
        // returns a copy

        // load size informations
        
        auto str_node_size = ini.get("size").get("node_size");
        auto str_link_size = ini.get("size").get("link_size");
        const size_t node_size = std::stoi(str_node_size);
        const size_t link_size = std::stoi(str_link_size);

        // load node informations
        for (size_t i = 0; i < node_size; i++)
        {
            auto str_node_index = std::to_string(i);
            auto str_node_id = ini.get("node" + str_node_index).get("node_id");
            auto str_node_type = ini.get("node" + str_node_index).get("node_type");
            auto str_node_pos_x = ini.get("node" + str_node_index).get("node_pos_x");
            auto str_node_pos_y = ini.get("node" + str_node_index).get("node_pos_y");

            int node_id = std::stoi(str_node_id);
            int node_type = std::stoi(str_node_type);
            int node_pos_x = std::stoi(str_node_pos_x);
            int node_pos_y = std::stoi(str_node_pos_y);
            create_node(node_id, static_cast<Node::NodeType>(node_type), ImVec2(node_pos_x, node_pos_y));
        }

        // load link informations
        for (size_t i = 0; i < link_size; i++)
        {
            auto str_link_index = std::to_string(i);
            auto str_link_id = ini.get("link" + str_link_index).get("link_id");
            auto str_link_end = ini.get("link" + str_link_index).get("link_end");
            auto str_link_start = ini.get("link" + str_link_index).get("link_start");

            int link_id = std::stoi(str_link_id);
            int link_end_attr = std::stoi(str_link_end);
            int link_start_attr = std::stoi(str_link_start);

            Link link;
            link.id = link_id;
            link.end_attr = link_end_attr;
            link.start_attr = link_start_attr;
            this->links.push_back(link);
        }
    }
    
}

void node_editor::Editor::turn_into_glsl()
{
    if (ImGui::Button("make glsl"))
    {
        auto rgba = interprete_result_color(*this, "node_editor_save_file.ini");
        generate_glsl(rgba);
    }
}

void node_editor::Editor::create_node(int current_id, Node::NodeType type, ImVec2 pos)
{
    const int node_id = current_id;
    ImNodes::SetNodeScreenSpacePos(node_id, pos);
    ImNodes::SnapNodeToGrid(node_id);

    switch (type)
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
    case node_editor::Node::NodeType::Vec2Node:
        this->nodes.push_back(new Vec2Node(node_id));
        break;
    case node_editor::Node::NodeType::Vec3Node:
        this->nodes.push_back(new Vec3Node(node_id));
        break;
    case node_editor::Node::NodeType::Vec4Node:
        this->nodes.push_back(new Vec4Node(node_id));
        break;
    case node_editor::Node::NodeType::ResultColorNode:
        this->nodes.push_back(std::move(ResultColorNode::get_instance(node_id)));
        break;
    case node_editor::Node::NodeType::TimeNode:
        this->nodes.push_back(new TimeNode(node_id));
        break;
    case node_editor::Node::NodeType::ConditionNode:
        this->nodes.push_back(new ConditionNode(node_id));
        break;
    case node_editor::Node::NodeType::SinFunctionNode :
        this->nodes.push_back(new SinFunctionNode(node_id));
        break;

    default:
        break;
    }
}

void node_editor::Editor::delete_node(int node_id)
{
    // FIXME: do allow user to delete more than one node.
    // FIXME: when any node is selected then selection is canceled, and if try to delete node it crashes!
    // FIXME: still there is some problems about link deletions
    if (node_id != -1)
    {
        int node_index = get_node_index_by_id(node_id);
        if (node_index != -1)
        {
            // first delete links
            for (size_t i = 0; i < this->links.size();)
            {
                bool _check = false;
                if ((links[i].end_attr > this->nodes[node_index]->id &&
                    links[i].end_attr < this->nodes[node_index]->last_id)
                    ||
                    (links[i].start_attr > this->nodes[node_index]->id &&
                    links[i].start_attr < this->nodes[node_index]->last_id)
                )
                {
                    size_t link_index = get_link_index_by_id(links[i].id);
                    
                    this->links.erase(this->links.begin() + link_index);
                    i = 0;
                    _check = true;
                }
                if(_check == false)
                    i++;
            }


            for(size_t j = node_index + 1; j < this->nodes.size(); j++)
            {
                auto pos = ImNodes::GetNodeEditorSpacePos(this->nodes.at(j)->id);
                this->nodes.at(j)->id -= (this->nodes.at(node_index)->last_id - this->nodes.at(node_index)->id);
                ImNodes::SetNodeEditorSpacePos(this->nodes.at(j)->id, pos);
            }

            delete this->nodes.at(node_index);
            this->nodes.erase(this->nodes.begin() + node_index);
                                                        //i
            if(ImNodes::IsNodeSelected(node_id))
                ImNodes::ClearNodeSelection(node_id);
        }
    }

}

// FIXME: add .ini file read/writing tosave current editor state in a different function.

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

    if (ImGui::Button("load shader file"))
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".glsl,.vert,.frag", "../..");
    
    ImGui::SameLine();
    ImGui::Text("%s", file_path_name.c_str());

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            file_path_name = ImGuiFileDialog::Instance()->GetFilePathName();
            std::cout << file_path_name << std::endl;
            // std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            
            // FIXME: fix the structure of screen_shader...
        }
        
        // close
        ImGuiFileDialog::Instance()->Close();
    }  

    if(ImGui::Button("compile shader"))
    {
        delete shader;
        glcompiler::init();
        shader = new Shader2D();
        //shader->load_shader_code("../../shaders/test_vert.glsl", Shader2D::ShaderCodeType::VERTEX_SHADER);
        shader->load_shader_code(file_path_name.c_str());
        glcompiler::compile_and_attach_shaders(shader);
    }

    editor.save();
    editor.load();
    editor.turn_into_glsl();
        

    ImGui::SetWindowFontScale(1.2);
    ImGui::TextColored({1.0, 0.0, 0.0, 1.0}, "%s", compiler_info.compile_log_info);
    ImGui::SetWindowFontScale(1.0);

    ImGui::EndChild();
    
}

void node_editor::EditorManager::show_shortcuts()
{
    ImGui::BeginChild("Shortcuts", ImVec2{300, 300},true);
    ImGui::TextColored(ImVec4(1.f, 0.81f, 0.52f, 1.f), "Press \'A\' to add new node.");
    ImGui::TextColored(ImVec4(1.f, 0.81f, 0.52f, 1.f), "Press \'D\' to delete selected node.");
    ImGui::EndChild();
}

