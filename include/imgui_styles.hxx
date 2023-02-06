#ifndef IMGUI_STYLES_HXX
#define IMGUI_STYLES_HXX

#ifdef IMSTYLE1
    style->WindowRounding = 5.3f;
    style->FrameRounding = 2.3f;
    style->ScrollbarRounding = 0;

    style->Colors[ImGuiCol_Text]                  = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
    style->Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style->Colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    style->Colors[ImGuiCol_ChildBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    style->Colors[ImGuiCol_Border]                = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    style->Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_FrameBg]               = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    style->Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    style->Colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
    style->Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    style->Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
    style->Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    style->Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    style->Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
    //style->Colors[ImGuiCol_ComboBg]               = ImVec4(0.1f, 0.1f, 0.1f, 0.99f);
    style->Colors[ImGuiCol_CheckMark]             = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    style->Colors[ImGuiCol_SliderGrab]            = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    style->Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    style->Colors[ImGuiCol_Button]                = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
    style->Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
    style->Colors[ImGuiCol_ButtonActive]          = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
    style->Colors[ImGuiCol_Header]                = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    style->Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive]          = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
    //style->Colors[ImGuiCol_Column]                = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    //style->Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    //style->Colors[ImGuiCol_ColumnActive]          = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    style->Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    style->Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    //style->Colors[ImGuiCol_CloseButton]           = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
    //style->Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
    //style->Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    style->Colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style->Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    //style->Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
#endif//IMSTYLE1

#ifdef IMSTYLE2
    //style->ChildWindowRounding = 3.f;
    style->GrabRounding = 0.f;
    style->WindowRounding = 0.f;
    style->ScrollbarRounding = 3.f;
    style->FrameRounding = 3.f;
    style->WindowTitleAlign = ImVec2(0.5f, 0.5f);

    style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = _MY_IM_COLOR1;
    //style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = _MY_IM_COLOR1;
    style->Colors[ImGuiCol_Border] = _MY_IM_COLOR2;
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    style->Colors[ImGuiCol_FrameBg] = _MY_IM_COLOR2;
    style->Colors[ImGuiCol_FrameBgHovered] = _MY_IM_COLOR2;
    style->Colors[ImGuiCol_FrameBgActive] = _MY_IM_COLOR2;
    style->Colors[ImGuiCol_TitleBg] = _MY_IM_COLOR3;
    style->Colors[ImGuiCol_TitleBgCollapsed] = _MY_IM_COLOR3;
    style->Colors[ImGuiCol_TitleBgActive] = _MY_IM_COLOR3;
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.26f, 0.56f, 0.56f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = _MY_IM_COLOR3;
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = _MY_IM_COLOR3;
    style->Colors[ImGuiCol_ScrollbarGrabActive] = _MY_IM_COLOR3;
    //style->Colors[ImGuiCol_ComboBg] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
    style->Colors[ImGuiCol_Button] = _MY_IM_COLOR3;
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    style->Colors[ImGuiCol_Header] = _MY_IM_COLOR3;
    style->Colors[ImGuiCol_HeaderHovered] = _MY_IM_COLOR3;
    style->Colors[ImGuiCol_HeaderActive] = _MY_IM_COLOR3;
    //style->Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    //style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    //style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = _MY_IM_COLOR3;
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    //style->Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    //style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    //style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.32f, 0.52f, 0.65f, 1.00f);
    //style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
#endif//IMSTYLE1

#ifdef IMSTYLE3
    ImVec4* colors = ImGui::GetStyle().Colors;
    unsigned int* imnodes_colors = ImNodes::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
    imnodes_colors[ImNodesCol_NodeOutline]              = vec4_2_uint(ImVec4(0.6f, 0.60f, 0.60f, 1.00f));
    imnodes_colors[ImNodesCol_NodeBackground]           = vec4_2_uint(ImVec4(0.10f, 0.10f, 0.10f, 1.00f));
    imnodes_colors[ImNodesCol_NodeBackgroundHovered]    = vec4_2_uint(ImVec4(0.20f, 0.20f, 0.20f, 1.00f));
    imnodes_colors[ImNodesCol_NodeBackgroundSelected]   = vec4_2_uint(ImVec4(0.30f, 0.30f, 0.30f, 1.00f));
    imnodes_colors[ImNodesCol_TitleBar]                 = vec4_2_uint(ImVec4(0.4f, 0.4f, 0.5f, 1.00f));
    imnodes_colors[ImNodesCol_TitleBarHovered]          = vec4_2_uint(ImVec4(0.44f, 0.44f, 0.55f, 1.00f));
    imnodes_colors[ImNodesCol_TitleBarSelected]         = vec4_2_uint(ImVec4(0.6f, 0.60f, 0.60f, 1.00f));
    imnodes_colors[ImNodesCol_Link]                     = vec4_2_uint(ImVec4(0.6f, 0.60f, 0.60f, 1.00f));
    imnodes_colors[ImNodesCol_LinkHovered]              = vec4_2_uint(ImVec4(0.6f, 0.60f, 0.60f, 1.00f));
    imnodes_colors[ImNodesCol_LinkSelected]             = vec4_2_uint(ImVec4(0.6f, 0.60f, 0.60f, 1.00f));
    imnodes_colors[ImNodesCol_Pin]                      = vec4_2_uint(ImVec4(0.6f, 0.60f, 0.60f, 1.00f));
    imnodes_colors[ImNodesCol_PinHovered]               = vec4_2_uint(ImVec4(0.6f, 0.60f, 0.60f, 1.00f));
    /*imnodes_colors[ImNodesCol_BoxSelector]
    imnodes_colors[ImNodesCol_BoxSelectorOutline]
    imnodes_colors[ImNodesCol_GridBackground]
    imnodes_colors[ImNodesCol_GridLine]
    imnodes_colors[ImNodesCol_GridLinePrimary]
    imnodes_colors[ImNodesCol_MiniMapBackground]
    imnodes_colors[ImNodesCol_MiniMapBackgroundHove]
    imnodes_colors[ImNodesCol_MiniMapOutline]
    imnodes_colors[ImNodesCol_MiniMapOutlineHovered]
    imnodes_colors[ImNodesCol_MiniMapNodeBackground]
    imnodes_colors[ImNodesCol_MiniMapNodeBackground]
    imnodes_colors[ImNodesCol_MiniMapNodeBackground]
    imnodes_colors[ImNodesCol_MiniMapNodeOutline]
    imnodes_colors[ImNodesCol_MiniMapLink]
    imnodes_colors[ImNodesCol_MiniMapLinkSelected]
    imnodes_colors[ImNodesCol_MiniMapCanvas]
    imnodes_colors[ImNodesCol_MiniMapCanvasOutline]*/

    //ImGuiStyle& style = ImGui::GetStyle();
    style->WindowPadding                     = ImVec2(8.00f, 8.00f);
    style->FramePadding                      = ImVec2(5.00f, 2.00f);
    style->CellPadding                       = ImVec2(6.00f, 6.00f);
    style->ItemSpacing                       = ImVec2(6.00f, 6.00f);
    style->ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
    style->TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
    style->IndentSpacing                     = 25;
    style->ScrollbarSize                     = 15;
    style->GrabMinSize                       = 10;
    style->WindowBorderSize                  = 1;
    style->ChildBorderSize                   = 1;
    style->PopupBorderSize                   = 1;
    style->FrameBorderSize                   = 1;
    style->TabBorderSize                     = 1;
    style->WindowRounding                    = 7;
    style->ChildRounding                     = 4;
    style->FrameRounding                     = 3;
    style->PopupRounding                     = 4;
    style->ScrollbarRounding                 = 9;
    style->GrabRounding                      = 3;
    style->LogSliderDeadzone                 = 4;
    style->TabRounding                       = 4;
#endif//IMSTYLE1

#ifdef IMSTYLE4
#endif//IMSTYLE1

#ifdef IMSTYLE5
#endif//IMSTYLE1

#endif//IMGUI_STYLES_HXX