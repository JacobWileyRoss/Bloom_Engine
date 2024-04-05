//
// Created by Jacob Ross on 4/4/24.
//

#ifndef BLOOM_ENGINEPROJECT_CODEEDITOR_H
#define BLOOM_ENGINEPROJECT_CODEEDITOR_H

#include <fstream>
#include <filesystem>
#include "imgui.h"

class CodeEditor {
public:
    CodeEditor() : filename(""), buffer("") {}

    void LoadFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (file.is_open()) {
            buffer.clear();
            std::string line;
            while (std::getline(file, line)) {
                buffer.append(line + "\n");
            }
            file.close();
            filename = filepath;
        }
    }

    void SaveFile() {
        if (!filename.empty()) {
            std::ofstream file(filename);
            if (file.is_open()) {
                file << buffer;
                file.close();
            }
        }
    }

    void Render() {
        ImGui::InputTextMultiline("##Editor", buffer.data(), buffer.size() + 1, ImVec2(-1, -1));
        //                                             ^^^^^^^^^^^^^^^
        // Use std::string::data() to get a pointer to the underlying character array
        if (ImGui::Button("Open")) {
            ImGui::OpenPopup("Open Lua Script");
        }
        if (ImGui::BeginPopup("Open Lua Script")) {
            if (ImGui::Selectable("Script 1")) {
                LoadFile("../../editor/Game/Scripts/script1.lua");
            }
            if (ImGui::Selectable("Script 2")) {
                LoadFile("../../editor/Game/Scripts/script2.lua");
            }
            ImGui::EndPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Save")) {
            SaveFile();
        }
    }

private:
    std::string filename;
    std::string buffer;
};

#endif //BLOOM_ENGINEPROJECT_CODEEDITOR_H
