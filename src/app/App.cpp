#include "app/App.hpp"

#include "ui/Theme.hpp"

#include <imgui.h>

#include <array>
#include <cstring>

namespace app {

App::App()
    : presetPath_("config/presets.json"),
      selectedSkinIndex_(-1),
      page_(NavPage::Catalog),
      searchBuffer_{},
      rarityFilter_(0) {
    std::memset(searchBuffer_, 0, sizeof(searchBuffer_));
}

void App::Load() {
    ui::ApplyTheme();
    skins_ = data::LoadPresets(presetPath_);
    if (!skins_.empty()) {
        selectedSkinIndex_ = 0;
    }
}

void App::Save() const {
    data::SavePresets(presetPath_, skins_);
}

void App::RenderSidebar() {
    ImGui::Begin("Navigation", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(220, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

    ImGui::TextUnformatted("Skin Studio");
    ImGui::Separator();

    if (ImGui::Selectable("Catalog", page_ == NavPage::Catalog)) {
        page_ = NavPage::Catalog;
    }
    if (ImGui::Selectable("Presets", page_ == NavPage::Presets)) {
        page_ = NavPage::Presets;
    }
    if (ImGui::Selectable("Settings", page_ == NavPage::Settings)) {
        page_ = NavPage::Settings;
    }

    ImGui::Spacing();
    if (ImGui::Button("Save presets")) {
        Save();
    }

    ImGui::End();
}

void App::RenderPreviewPanel() const {
    ImGui::Begin("Preview", nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2(230, 400), ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(450, 260), ImGuiCond_Once);

    ImGui::TextUnformatted("Preview panel");
    ImGui::Separator();

    const auto hasSelection = selectedSkinIndex_ >= 0 && selectedSkinIndex_ < static_cast<int>(skins_.size());
    if (!hasSelection) {
        ImGui::TextDisabled("No skin selected.");
        ImGui::End();
        return;
    }

    const auto& item = skins_[selectedSkinIndex_];
    ImGui::Text("Skin: %s", item.name.c_str());
    ImGui::Text("Placeholder image: %s", item.previewImage.string().c_str());

    const ImVec2 panelPos = ImGui::GetCursorScreenPos();
    const ImVec2 panelSize(360, 160);
    ImGui::GetWindowDrawList()->AddRectFilled(panelPos, ImVec2(panelPos.x + panelSize.x, panelPos.y + panelSize.y), IM_COL32(45, 55, 70, 255), 8.0F);
    ImGui::GetWindowDrawList()->AddText(ImVec2(panelPos.x + 16, panelPos.y + 70), IM_COL32(210, 220, 235, 255), "Image placeholder");
    ImGui::Dummy(panelSize);

    ImGui::End();
}

void App::RenderContent() {
    switch (page_) {
        case NavPage::Catalog:
            windows::DrawCatalogWindow(skins_, selectedSkinIndex_, searchBuffer_, rarityFilter_);
            windows::DrawEditorWindow((selectedSkinIndex_ >= 0 && selectedSkinIndex_ < static_cast<int>(skins_.size())) ? &skins_[selectedSkinIndex_] : nullptr);
            RenderPreviewPanel();
            break;
        case NavPage::Presets:
            ImGui::Begin("Presets", nullptr, ImGuiWindowFlags_NoCollapse);
            ImGui::SetWindowPos(ImVec2(230, 20), ImGuiCond_Once);
            ImGui::SetWindowSize(ImVec2(900, 340), ImGuiCond_Once);
            ImGui::Text("Loaded presets: %d", static_cast<int>(skins_.size()));
            ImGui::TextDisabled("Presets are auto-loaded from config/presets.json on startup.");
            if (ImGui::Button("Save now")) {
                Save();
            }
            ImGui::End();
            break;
        case NavPage::Settings:
            ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoCollapse);
            ImGui::SetWindowPos(ImVec2(230, 20), ImGuiCond_Once);
            ImGui::SetWindowSize(ImVec2(900, 340), ImGuiCond_Once);
            ImGui::TextUnformatted("Offline editor mode");
            ImGui::BulletText("No cheat functions");
            ImGui::BulletText("No injector or memory hooks");
            ImGui::BulletText("Only local JSON preset editing");
            ImGui::End();
            break;
    }
}

void App::Render() {
    RenderSidebar();
    RenderContent();
}

} // namespace app
