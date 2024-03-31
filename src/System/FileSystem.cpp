//
// Created by Jacob Ross on 3/29/24.
//

#include "../../include/System/FileSystem.h"

// Check for changes in Lua scripts to hot reload asset changes
void FileSystem::checkAndReloadScript(sol::state &lua, const std::string &scriptPath, std::time_t &lastModifiedTime) {

    // Check the last modified time of the file
    std::time_t currentModifiedTime = std::filesystem::last_write_time(scriptPath).time_since_epoch().count();

    // If the file has been modified since last check, reload it
    if (currentModifiedTime != lastModifiedTime) {
        lua.script_file(scriptPath);
        // Destroys all entities in state, this ensures they aren't duplicated during hot reload
        lua["destroyEntities"]();
        lua["constructLevel"]();

        // Update the last modified time to the current
        lastModifiedTime = currentModifiedTime;

        std::cout << "[INFO] Reloaded Lua script: " << scriptPath << std::endl;
    }
}