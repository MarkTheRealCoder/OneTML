//
// Created by marco on 17/11/2024.
//

#ifndef ONETML_PATH_H
#define ONETML_PATH_H

#define NORMALIZED_SEPARATOR '/'
#define WINDOWS_SEPARATOR '\\'

class Path {
private:
    std::string path;
    static void adaptPathElements(std::string& path, std::string& file);
public:
    explicit Path(const std::string& path);

    template <typename T>
    Path operator/(T&& file) {
        std::string file_str = std::forward<T>(file);
        adaptPathElements(path, file_str);
        return Path(path + file);
    };
    template <typename T>
    void operator/=(T&& file) {
        std::string file_str = std::forward<T>(file);
        adaptPathElements(path, file_str);
        this->path += file_str;
    }

    std::string operator!() const;

};


#endif //ONETML_PATH_H
