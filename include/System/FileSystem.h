//
// Created by Jacob Ross on 3/29/24.
//

#ifndef BLOOM_ENGINE_FILESYSTEM_H
#define BLOOM_ENGINE_FILESYSTEM_H

#include <iostream>
#include <filesystem>
#include <sol/sol.hpp>


class FileSystem {
public:

    // Check for changes in Lua scripts to hot reload asset changes
    void checkAndReloadScript(sol::state& lua, const std::string& scriptPath, std::time_t& lastModifiedTime) {
        // Check the last modified time of the file
        std::time_t currentModifiedTime = std::filesystem::last_write_time(scriptPath).time_since_epoch().count();

        if (currentModifiedTime != lastModifiedTime) {
            // The file has been modified since last check, reload it
            lua.script_file(scriptPath);
            // Destroys all entities in state so they aren't duplicated during hot reload
            lua["destroyEntities"]();
            lua["constructLevel"]();

            // Update the last modified time to the current
            lastModifiedTime = currentModifiedTime;

            std::cout << "[INFO] Reloaded Lua script: " << scriptPath << std::endl;
        }
    }

};


#endif //BLOOM_ENGINE_FILESYSTEM_H
