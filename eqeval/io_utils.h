#ifndef EQEVAL_IO_UTILS_H_
#define EQEVAL_IO_UTILS_H_

#include <string>
#include <vector>

namespace eqeval {
namespace io_utils {

    std::vector<std::string> readEquationsFromFile(const std::string &input_file_path);

} // namespace io_utils
} // namespace eqeval

#endif // EQEVAL_IO_UTILS_H_