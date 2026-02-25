#include "app/App.hpp"

#include <imgui.h>

#include <cfloat>
#include <cstdio>

namespace app::windows {

void DrawEditorWindow(data::SkinItem* selectedSkin) {
    ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2(690, 20), ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(440, 360), ImGuiCond_Once);

    if (selectedSkin == nullptr) {
        ImGui::TextDisabled("Select a skin in catalog to edit details.");
        ImGui::End();
        return;
    }

    ImGui::Text("Editing: %s", selectedSkin->name.c_str());
    ImGui::Separator();

    ImGui::SliderFloat("Wear", &selectedSkin->wear, 0.00F, 1.00F, "%.3f");
    ImGui::Checkbox("StatTrak", &selectedSkin->statTrak);
    ImGui::InputInt("Seed", &selectedSkin->seed);

    static char notesBuffer[512] = {};
    if (notesBuffer[0] == '\0') {
        std::snprintf(notesBuffer, sizeof(notesBuffer), "%s", selectedSkin->notes.c_str());
    }

    if (ImGui::InputTextMultiline("Notes", notesBuffer, sizeof(notesBuffer), ImVec2(-FLT_MIN, 120))) {
        selectedSkin->notes = notesBuffer;
    }

    ImGui::End();
}

} // namespace app::windows
