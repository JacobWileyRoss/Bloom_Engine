//
// Created by Jacob Ross on 4/4/24.
//

#ifndef BLOOM_ENGINEPROJECT_CONSOLESTREAMBUFFER_H
#define BLOOM_ENGINEPROJECT_CONSOLESTREAMBUFFER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class ConsoleStreamBuffer : public std::streambuf {
public:
    ConsoleStreamBuffer(std::ostream& stream, std::size_t maxLines = 1000) : stream_(stream), maxLines_(maxLines) {
        lineBuffer_.reserve(128);
    }

    const std::vector<std::string>& GetLines() const {
        return lines_;
    }

protected:
    int_type overflow(int_type ch) override {
        if (ch != EOF) {
            lineBuffer_.push_back(ch);
        }
        if (ch == '\n' || ch == EOF) {
            lines_.push_back(std::string(lineBuffer_.data(), lineBuffer_.size()));
            if (lines_.size() > maxLines_) {
                lines_.erase(lines_.begin());
            }
            lineBuffer_.clear();
        }
        return ch;
    }

    std::streamsize xsputn(const char_type* s, std::streamsize count) override {
        const auto bufferSize = static_cast<std::size_t>(std::min<std::streamsize>(count, std::numeric_limits<std::streamsize>::max()));
        lineBuffer_.insert(lineBuffer_.end(), s, s + bufferSize);
        if (std::find(s, s + count, '\n') != s + count) {
            lines_.push_back(std::string(lineBuffer_.data(), lineBuffer_.size()));
            if (lines_.size() > maxLines_) {
                lines_.erase(lines_.begin());
            }
            lineBuffer_.clear();
        }
        return count;
    }

private:
    std::ostream& stream_;
    std::vector<char> lineBuffer_;
    std::vector<std::string> lines_;
    std::size_t maxLines_;
};

#endif //BLOOM_ENGINEPROJECT_CONSOLESTREAMBUFFER_H
