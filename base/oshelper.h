/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the “Software”), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once
#include <string.h>

#include <filesystem>
#include <set>

namespace base {
/**
 * @brief Creates a temporary directory and returns it to the caller
 *
 * Directory will be at location intended for temporary files / dirs.
 * Directory name will be using the given prefix + 6 random alphanum chars
 * E.g. on a typical Linux system if called with 'foo' as dir_prefix
 * the returned directory will be something like /tmp/fooEn7tX5
 *
 * @param dir_prefix   Prefix for the directory-name
 * @return std::filesystem::path  The newly created temporary directory
 */
inline std::filesystem::path createTempDir(const std::string& dir_prefix) {
    std::string main_temp_folder = std::filesystem::temp_directory_path() / (dir_prefix + "XXXXXX");

    char dir_cstr[255] = "";
    strncpy(dir_cstr, main_temp_folder.c_str(), 254);
    mkdtemp(dir_cstr);

    std::filesystem::path dir{dir_cstr};
    std::filesystem::create_directory(dir);

    return dir;
}

inline std::set<std::filesystem::path> getDirContents(const std::filesystem::path& dir) {
    std::set<std::filesystem::path> paths;
    std::copy(std::filesystem::directory_iterator(dir), std::filesystem::directory_iterator(),
              std::inserter(paths, paths.end()));

    return paths;
}
}  // namespace base