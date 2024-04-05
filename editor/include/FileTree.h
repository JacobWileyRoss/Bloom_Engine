//
// Created by Jacob Ross on 4/4/24.
//

#ifndef BLOOM_ENGINEPROJECT_FILETREE_H
#define BLOOM_ENGINEPROJECT_FILETREE_H

#include <filesystem>
#include "../imgui.h"
#include "CodeEditor.h"


class FileTree {
public:
    FileTree() : selectedFilePath("") {}

    void DisplayFileTree(const std::filesystem::path& path, CodeEditor& codeEditor) {
        if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
            ImGui::Text("Invalid directory");
            return;
        }

        ImGui::BeginChild("FileTree", ImVec2(0, 0), true);
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const auto filename = entry.path().filename().string();
            if (std::filesystem::is_directory(entry.status())) {
                if (ImGui::TreeNode(filename.c_str())) {
                    DisplayFileTree(entry.path(), codeEditor); // Recursive call for subdirectories
                    ImGui::TreePop();
                }
            } else {
                // Display selectable file names
                if (ImGui::Selectable(filename.c_str())) {
                    selectedFilePath = entry.path().string();
                }
                // Handle double-click event
                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                    codeEditor.LoadFile(selectedFilePath);
                }
            }
        }
        ImGui::EndChild();
    }

private:
    std::string selectedFilePath;
};

#endif //BLOOM_ENGINEPROJECT_FILETREE_H
