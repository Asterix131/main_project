#include "ui/Theme.hpp"

#include <imgui.h>

namespace ui {

void ApplyTheme() {
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 7.0F;
    style.FrameRounding = 5.0F;
    style.GrabRounding = 5.0F;
    style.TabRounding = 4.0F;
    style.WindowBorderSize = 1.0F;

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.08F, 0.09F, 0.11F, 1.00F);
    colors[ImGuiCol_Header] = ImVec4(0.20F, 0.28F, 0.44F, 1.00F);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.31F, 0.43F, 0.66F, 1.00F);
    colors[ImGuiCol_Button] = ImVec4(0.18F, 0.27F, 0.42F, 1.00F);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.28F, 0.39F, 0.62F, 1.00F);
}

} // namespace ui
