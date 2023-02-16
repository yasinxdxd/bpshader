#ifndef NODE_EDITOR_HPP
#define NODE_EDITOR_HPP

#include <vector>
#include <string>

struct ImVec2;
struct ImNodesEditorContext;
class Texture2D;
class Shader2D;


#define NODE_OPERATOR Node
#define NODE_VARIABLE Node
#define NODE_BUILTIN Node

namespace node_editor
{
    struct Editor;

    typedef float _InputType;
    typedef float _OutputType;
    struct Node
    {
        enum NodeType
        {
            MultiplyNode,
            AdditionNode,
            FloatNode,
            BoolNode,
            TimeNode,
            ConditionNode,
            SinFunctionNode,
            NodeType_COUNT
        };

        NodeType type;
        int id;
        int last_id;
        // FIXME: input types are only C float. It should be improved and should allowed to get input as vector and matrix types.
        std::vector<_InputType> inputs;
        std::vector<_OutputType> outputs;

        Editor* m_editor;
        Node(const int i, NodeType t) : id(i), type(t) {}

        virtual int show() = 0;

    };

    struct MultiplyNode : public NODE_OPERATOR
    {
        MultiplyNode(const int i);

        virtual int show() override;
    };

    struct AdditionNode : public NODE_OPERATOR
    {
        AdditionNode(const int i);

        virtual int show() override;
    };

    struct FloatNode : public NODE_VARIABLE
    {
        char var_name[64];
        FloatNode(const int i);

        virtual int show() override;
    };

    struct BoolNode : public NODE_VARIABLE
    {
        BoolNode(const int i);

        virtual int show() override;
    };

    // TODO: implement these variable nodes...
    struct Vec2Node : public NODE_VARIABLE
    {
        Vec2Node(const int i);

        virtual int show() override;
    };

    struct Vec3Node : public NODE_VARIABLE
    {
        Vec3Node(const int i);

        virtual int show() override;
    };

    struct Vec4Node : public NODE_VARIABLE
    {
        Vec4Node(const int i);

        virtual int show() override;
    };

    // TODO: implement the time uniform value from the shader to TimeNode itself to be shown
    struct TimeNode : public NODE_BUILTIN
    {
        TimeNode(const int i);

        virtual int show() override;
    };

    struct ConditionNode : public NODE_OPERATOR
    {
        ConditionNode(const int i);

        static inline const char* items[6] = {"    ==", "    !=", "     <", "     >", "    <=", "    >="};
        uint8_t item_index = 0;
        const char* current_item = items[item_index];
        
        virtual int show() override;
    };

    struct SinFunctionNode : public NODE_BUILTIN
    {
        SinFunctionNode(const int i);

        static inline const char* items[2] = {"radian", "degree"};
        uint8_t item_index = 0;
        const char* current_item = items[item_index];

        virtual int show() override;
    };

    struct CustomFunctionNode : public NODE_BUILTIN
    {
        // TODO: allow user to create custom functions via this node...
        // TODO: allow user to write glsl code in to it...
    };
    

    struct Link
    {
        int id;
        int start_attr, end_attr;
    };

    struct Editor
    {
        char window_name[32];
        ImNodesEditorContext* context = nullptr;
        std::vector<Node*>    nodes;
        std::vector<Link>     links;
        int                   current_id = 0;
        int                   current_link_id = 0;

        int selected_node_ids[64];
        bool right_click_menu = false;

        //...

        void show_editor();
        Node* get_node_by_id(uint64_t id) const;
        size_t get_node_index_by_id(uint64_t id) const;
        size_t get_link_index_by_id(uint64_t id) const;
        void initialize(const char* editor_name);
        void shutdown();
        void save();
        void load();
        void create_node(int current_id, Node::NodeType type, ImVec2 pos);
        void delete_node(int node_id);
    };   

    struct EditorManager
    {
        static inline const char* const items[Node::NodeType::NodeType_COUNT] = {
            "Multiply", "Add", "Float1", "Bool", "Time", "Condition", "SinFunctionNode"
        };
        static inline int item_current_idx = 0; // Here we store our selection data as an index.
        static inline std::string file_path_name = "../../shaders/notexture_frag.glsl";
        static void show_node_list();
        static void show_shader_screen(Editor& editor, Texture2D*& texture, Shader2D*& shader);
        static void show_shortcuts();
    };

    // TODO: make a text editor part
    struct TextEditor
    {
        // TODO: tokenize code and color the keywords.
        // additionally you can add (ctrl + space) auto complete...
    };

}


#endif//NODE_EDITOR_HPP