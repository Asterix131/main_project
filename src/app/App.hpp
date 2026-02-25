#pragma once

#include "data/SkinItem.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace app {

class App {
public:
    App();

    void Load();
    void Save() const;
    void Render();

private:
    enum class NavPage { Catalog = 0, Presets = 1, Settings = 2 };

    std::filesystem::path presetPath_;
    std::vector<data::SkinItem> skins_;
    int selectedSkinIndex_;

    NavPage page_;
    char searchBuffer_[128];
    int rarityFilter_;

    void RenderSidebar();
    void RenderContent();
    void RenderPreviewPanel() const;
};

namespace windows {

void DrawCatalogWindow(std::vector<data::SkinItem>& skins, int& selectedSkinIndex, char* searchBuffer, int& rarityFilter);
void DrawEditorWindow(data::SkinItem* selectedSkin);

} // namespace windows

} // namespace app
