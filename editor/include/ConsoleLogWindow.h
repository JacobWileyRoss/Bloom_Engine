//
// Created by Jacob Ross on 4/4/24.
//

#ifndef BLOOM_ENGINEPROJECT_CONSOLELOGWINDOW_H
#define BLOOM_ENGINEPROJECT_CONSOLELOGWINDOW_H
#include <vector>
#include "../imgui.h"


class ConsoleLogWindow {
    public:

    // Custom output window with auto-scrolling
    void ShowConsoleLogWindow(const std::vector<std::string>& lines) {
        ImGui::Begin("Console Log");
        ImGui::BeginChild("ScrollingRegion", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,1));

        // Iterate through lines and display them
        for (const auto& line : lines) {
            ImGui::TextUnformatted(line.c_str());
        }

        // Automatically scroll to the bottom
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::End();
    }
};

#endif //BLOOM_ENGINEPROJECT_CONSOLELOGWINDOW_H
