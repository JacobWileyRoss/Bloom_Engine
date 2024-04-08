//
// Created by Jacob Ross on 4/7/24.
//

#ifndef BLOOM_ENGINE_OPERATIONSLOG_H
#define BLOOM_ENGINE_OPERATIONSLOG_H

#include <iostream>
#include <sstream>
#include <vector>


class OperationsLog {
public:
    void logOperation(const std::string& operation) {
        operations.push_back(operation);
    }

    // Get all logged operations as a single string, each operation separated by a newline
    std::string getLoggedOperations() const {
        std::stringstream ss;
        for (const auto& operation : operations) {
            ss << operation << std::endl; // Append each operation followed by a newline
        }
        return ss.str();
    }

    void clear() {
        operations.clear();
    }

private:
    std::vector<std::string> operations;

};


#endif //BLOOM_ENGINE_OPERATIONSLOG_H
