//
// Created by Jacob Ross on 4/4/24.
//

#ifndef BLOOM_ENGINEPROJECT_CONSOLELOGWINDOW_H
#define BLOOM_ENGINEPROJECT_CONSOLELOGWINDOW_H
#include <vector>
#include "../../vendor/imgui-docking/imgui.h"


class ConsoleLogWindow {
    public:

    // Custom output window with auto-scrolling
    void ShowConsoleLogWindow(const std::vector<std::string>& lines) {

        //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255.0f, 0, 135.0f, 0.3f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255.0f, 255.0f, 255.0f, 255.0f));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_TableRowBg, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,1));
        ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, ImVec4(255.0f, 0, 135.0f, 0.6f));


        ImGui::Begin("Console Log");
        ImGui::BeginChild("ScrollingRegion", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);

        // Iterate through lines and display them
        for (const auto& line : lines) {
            ImGui::TextUnformatted(line.c_str());
        }

        // Automatically scroll to the bottom
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::End();
    }
};

#endif //BLOOM_ENGINEPROJECT_CONSOLELOGWINDOW_H
