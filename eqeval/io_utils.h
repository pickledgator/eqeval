#ifndef EQEVAL_IO_UTILS_H_
#define EQEVAL_IO_UTILS_H_

#include <string>
#include <vector>

namespace eqeval {
namespace io_utils {

/* Reads a equations file from disk as a vector of strings
 * The format of the input file should be composed of tokens as "variables", "operators", and "numbers"
 * where variables contain alpha characters only, operators are limited to only "+" and numbers are
 * contained to fit within an unsigned long.
 * 
 * Each equation should be on its own line, and each token should be separated by at least one white space.
 * Example equations file:
 * a = 1 + 2
 * b = a + 3 + 4
 * d = c + b + a
 * c = 1 + 4 + 2
 *
 * @param input_file_path Path to the equations file on disk
 * @returns vector of strings where each line of the equations file is an element in the vector
 * @throws std::exception is file can't be found
 */
std::vector<std::string> readEquationsFromFile(const std::string &input_file_path);

} // namespace io_utils
} // namespace eqeval

#endif // EQEVAL_IO_UTILS_H_