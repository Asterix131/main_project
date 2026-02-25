#include "app/App.hpp"

#include <imgui.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <string>

namespace app::windows {
namespace {

std::string ToLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return value;
}

} // namespace

void DrawCatalogWindow(std::vector<data::SkinItem>& skins, int& selectedSkinIndex, char* searchBuffer, int& rarityFilter) {
    ImGui::Begin("Catalog", nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2(230, 20), ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(450, 360), ImGuiCond_Once);

    ImGui::InputTextWithHint("##search", "Search by skin or weapon...", searchBuffer, 128);

    constexpr std::array<const char*, 6> rarityOptions = {
        "All rarities", "Consumer Grade", "Industrial Grade", "Mil-Spec", "Classified", "Contraband"};
    ImGui::Combo("Rarity", &rarityFilter, rarityOptions.data(), static_cast<int>(rarityOptions.size()));
    ImGui::Separator();

    const std::string search = ToLower(searchBuffer);

    for (int i = 0; i < static_cast<int>(skins.size()); ++i) {
        const auto& skin = skins[i];
        const std::string haystack = ToLower(skin.name + " " + skin.weapon);

        const bool matchedBySearch = search.empty() || haystack.find(search) != std::string::npos;
        const bool matchedByRarity = rarityFilter == 0 || skin.rarity == rarityOptions[rarityFilter];
        if (!matchedBySearch || !matchedByRarity) {
            continue;
        }

        const bool selected = selectedSkinIndex == i;
        if (ImGui::Selectable((skin.name + "##" + skin.id).c_str(), selected)) {
            selectedSkinIndex = i;
        }
        ImGui::SameLine();
        ImGui::TextDisabled("(%s)", skin.weapon.c_str());
    }

    ImGui::End();
}

} // namespace app::windows
