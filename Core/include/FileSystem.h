//
// Created by Jacob Ross on 3/29/24.
//

#ifndef BLOOM_ENGINE_FILESYSTEM_H
#define BLOOM_ENGINE_FILESYSTEM_H

#include <iostream>
#include <filesystem>
#include <../../../vendor/sol2/include/sol/sol.hpp>


class FileSystem {
public:
    void checkAndReloadScript(sol::state& lua, const std::string& scriptPath, std::time_t& lastModifiedTime);

};


#endif //BLOOM_ENGINE_FILESYSTEM_H
