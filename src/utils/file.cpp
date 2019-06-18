#include "file.h"

namespace file_utils {

    bool exists(std::string &file_name) {
        struct stat buf{};
        return (stat(file_name.c_str(), &buf) == 0);
    }

    std::string raw_read(std::string &file_name) {
        if (!exists(file_name)) return nullptr;
        FILE* fp = fopen(file_name.c_str(), "r");
        std::string buf;
        if (fp == nullptr)
            return buf;

        char* line = nullptr;
        size_t len = 0;
        while ((getline(&line, &len, fp)) != -1) {
            buf += line;
        }
        fclose(fp);
        if (line)
            free(line);
        return buf;
    }
}
