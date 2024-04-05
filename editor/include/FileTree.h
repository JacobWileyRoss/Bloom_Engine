//
// Created by Jacob Ross on 4/4/24.
//

#ifndef BLOOM_ENGINEPROJECT_FILETREE_H
#define BLOOM_ENGINEPROJECT_FILETREE_H

#include <filesystem>
#include "imgui.h"


class FileTree {
public:

    void DisplayFileTree(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
        ImGui::Text("Invalid directory");
        return;
    }

        ImGui::BeginChild("FileTree", ImVec2(0, 0), true);
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const auto filename = entry.path().filename().string();
            if (std::filesystem::is_directory(entry.status())) {
                if (ImGui::TreeNode(filename.c_str())) {
                    DisplayFileTree(entry.path()); // Recursive call for subdirectories
                    ImGui::TreePop();
                }
            } else {
                ImGui::Text("%s", filename.c_str());
            }
        }

        ImGui::EndChild();
    }

};

#endif //BLOOM_ENGINEPROJECT_FILETREE_H
