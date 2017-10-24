#include "pandora/Support/Utils.h"

#include <boost/filesystem.hpp>

namespace pandora {

std::string ReadUtf8File(const fs::path &filepath) {
  // fs::is_empty() can throw basic_filesystem_error<path>
  // in case filepath doesn't  exist, or
  // in case filepath's file_status is "other".
  // "other" in this case means everything that is not regular file,
  // directory or a symlink.
  if (!fs::is_empty(filepath) && fs::is_regular_file(filepath)) {
    fs::ifstream file(filepath, std::ios::in | std::ios::binary);
    std::vector<char> contents((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
    return std::string(contents.begin(), contents.end());
  }
  return std::string();
}

void WriteUtf8File(const fs::path &filepath, const std::string &contents) {
  fs::ofstream file;
  file.open(filepath);
  file << contents;
  file.close();
}
} // namespace pandora
