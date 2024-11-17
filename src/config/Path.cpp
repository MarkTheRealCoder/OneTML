//
// Created by marco on 17/11/2024.
//

#include <string>
#include <regex>

#include "Path.h"

inline std::string replaceSeparators(const std::string& str, const char from, const char to) {
    auto new_str = const_cast<char*>(str.c_str());
    for (int i = 0; i < str.size(); i++) {
        if (new_str[i] == from) {
            new_str[i] = to;
        }
    }
    return {new_str};
}

inline bool is_file(const std::string& path) {
    return regex_match(path, std::regex(".*\\.(html|json|js)$", std::regex_constants::icase));
}

inline std::string normalize_path(const std::string& path) {
    auto new_path = path;
#ifdef _WIN32
    new_path = replaceSeparators(path, WINDOWS_SEPARATOR, NORMALIZED_SEPARATOR);
#endif
    return path.ends_with(NORMALIZED_SEPARATOR) || is_file(new_path) ? new_path : new_path + NORMALIZED_SEPARATOR;
}

Path::Path(const std::string& path): path(normalize_path(path)) {}

void Path::adaptPathElements(std::string &this_path, std::string &file) {
    // PATH
    if (is_file(this_path)) {
        throw std::invalid_argument("Invalid path: " + this_path + " cannot be extended.");
    }
    if (!this_path.ends_with(NORMALIZED_SEPARATOR)) {
        this_path += NORMALIZED_SEPARATOR;
    }

    // FILE
    file = normalize_path(file);
    file = (file.starts_with(NORMALIZED_SEPARATOR)) ? file.substr(1) : file;
}

std::string Path::operator!() const {
    auto new_path = path;
    #ifdef _WIN32
    new_path = replaceSeparators(path, NORMALIZED_SEPARATOR, WINDOWS_SEPARATOR);
    #endif
    return new_path;
}