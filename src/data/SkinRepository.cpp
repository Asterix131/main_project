#include "data/SkinItem.hpp"

#include <filesystem>
#include <fstream>
#include <iomanip>

#include <nlohmann/json.hpp>

namespace data {
namespace {

using json = nlohmann::json;

json ToJson(const SkinItem& item) {
    return {
        {"id", item.id},
        {"name", item.name},
        {"weapon", item.weapon},
        {"rarity", item.rarity},
        {"wear", item.wear},
        {"statTrak", item.statTrak},
        {"seed", item.seed},
        {"notes", item.notes},
        {"preview", item.previewImage.generic_string()},
    };
}

SkinItem FromJson(const json& raw) {
    SkinItem item;
    item.id = raw.value("id", "");
    item.name = raw.value("name", "Unknown Skin");
    item.weapon = raw.value("weapon", "Unknown Weapon");
    item.rarity = raw.value("rarity", "Consumer Grade");
    item.wear = raw.value("wear", 0.15F);
    item.statTrak = raw.value("statTrak", false);
    item.seed = raw.value("seed", 1);
    item.notes = raw.value("notes", "");
    item.previewImage = raw.value("preview", "assets/preview_placeholder.txt");
    return item;
}

std::vector<SkinItem> DefaultSkins() {
    return {
        SkinItem{"ak47_redline", "AK-47 | Redline", "AK-47", "Classified", 0.12F, true, 101, "Starter preset", "assets/preview_placeholder.txt"},
        SkinItem{"m4a4_howl", "M4A4 | Howl", "M4A4", "Contraband", 0.03F, false, 777, "Use sparingly", "assets/preview_placeholder.txt"},
    };
}

} // namespace

bool SavePresets(const std::filesystem::path& presetPath, const std::vector<SkinItem>& skins) {
    std::error_code ec;
    std::filesystem::create_directories(presetPath.parent_path(), ec);

    json output;
    output["skins"] = json::array();
    for (const auto& skin : skins) {
        output["skins"].push_back(ToJson(skin));
    }

    std::ofstream outFile(presetPath);
    if (!outFile.is_open()) {
        return false;
    }

    outFile << std::setw(2) << output << '\n';
    return static_cast<bool>(outFile);
}

std::vector<SkinItem> LoadPresets(const std::filesystem::path& presetPath) {
    std::ifstream inFile(presetPath);
    if (!inFile.is_open()) {
        const auto defaults = DefaultSkins();
        SavePresets(presetPath, defaults);
        return defaults;
    }

    json parsed;
    try {
        inFile >> parsed;
    } catch (const json::parse_error&) {
        const auto defaults = DefaultSkins();
        SavePresets(presetPath, defaults);
        return defaults;
    }

    std::vector<SkinItem> skins;
    if (parsed.contains("skins") && parsed["skins"].is_array()) {
        for (const auto& skinRaw : parsed["skins"]) {
            skins.push_back(FromJson(skinRaw));
        }
    }

    if (skins.empty()) {
        skins = DefaultSkins();
    }

    return skins;
}

} // namespace data
