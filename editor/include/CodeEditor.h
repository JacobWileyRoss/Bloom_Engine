//
// Created by Jacob Ross on 4/4/24.
//

#ifndef BLOOM_ENGINEPROJECT_CODEEDITOR_H
#define BLOOM_ENGINEPROJECT_CODEEDITOR_H

#include <fstream>
#include <filesystem>
#include "../imgui.h"

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
        // Set background color to black
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Text color to white
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Window background color to black

        // Begin the CodeEditor window with ImGuiWindowFlags_NoBackground flag to set the background color to black
        ImGui::Begin("Code Editor", nullptr, ImGuiWindowFlags_NoBackground);

        // InputTextMultiline function to display the text editor
        ImGui::InputTextMultiline("##Editor", buffer.data(), buffer.size() + 1, ImVec2(-1, -1));

        // End the CodeEditor window
        ImGui::End();

        // Restore the default style colors
        ImGui::PopStyleColor(2); // Pop the pushed style colors outside the Render function


        // Use std::string::data() to get a pointer to the underlying character array
        if (ImGui::Button("Open")) {
            // Show file dialog when "Open" button is clicked
            ImGui::OpenPopup("Open Source File");
        }
        if (ImGui::BeginPopup("Open Lua Script")) {
            // Iterate over files in the directory and display them as selectable options
            for (const auto& entry : std::filesystem::directory_iterator("../../editor/Game/src")) {
                if (!entry.is_directory()) {
                    if (ImGui::Selectable(entry.path().filename().string().c_str())) {
                        // Load the selected file
                        LoadFile(entry.path().string());
                    }
                }
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
