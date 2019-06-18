#ifndef GL_SKELETON_FILE_H
#define GL_SKELETON_FILE_H
#include <string>
#include <sys/stat.h>
#include <fstream>

namespace file_utils {
    bool exists(std::string& file_name);
    std::string raw_read(std::string& file_name);
}
#endif
