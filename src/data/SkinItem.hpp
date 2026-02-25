#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace data {

struct SkinItem {
    std::string id;
    std::string name;
    std::string weapon;
    std::string rarity;
    float wear = 0.15F;
    bool statTrak = false;
    int seed = 1;
    std::string notes;
    std::filesystem::path previewImage;
};

std::vector<SkinItem> LoadPresets(const std::filesystem::path& presetPath);
bool SavePresets(const std::filesystem::path& presetPath, const std::vector<SkinItem>& skins);

} // namespace data
