#ifndef _3DRENDERER_EDITOR_HPP
#define _3DRENDERER_EDITOR_HPP

class Texture2D;
class Shader;

namespace renderer_editor
{
    void show(Texture2D*& texture)
    {
        ImGui::SetNextWindowPos(ImVec2{0, 0});
        ImGui::SetNextWindowSize(ImVec2{800, 600});
        ImGui::Begin("3d renderer");
        
        ImGui::Image(*texture, {800, 600}, {-1, 1}, {0, 0});
        
        ImGui::End();
    }
}

#endif//3DRENDERER_EDITOR_HPP