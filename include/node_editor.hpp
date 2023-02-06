#ifndef NODE_EDITOR_HPP
#define NODE_EDITOR_HPP

#include <vector>

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
            NodeType_COUNT
        };

        NodeType type;
        int id;
        int last_id;
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

    struct TimeNode : public NODE_BUILTIN
    {
        TimeNode(const int i);

        virtual int show() override;
    };

    struct ConditionNode : public NODE_OPERATOR
    {
        ConditionNode(const int i);
        
        virtual int show() override;
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

        //...

        void show_editor();
        Node* get_node_by_id(uint64_t id) const;
        size_t get_node_index_by_id(uint64_t id) const;
        void initialize(const char* editor_name);
        void shutdown();
        void save();
        void load();
    };   

    struct EditorManager
    {
        static inline const char* const items[Node::NodeType::NodeType_COUNT] = {
            "Multiply", "Add", "Float1", "Bool", "Time", "Condition"
        };
        static inline int item_current_idx = 0; // Here we store our selection data as an index.
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