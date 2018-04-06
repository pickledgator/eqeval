#include "eqeval/io_utils.h"
#include "eqeval/exception.h"
#include <fstream>

namespace eqeval {
namespace io_utils {

std::vector<std::string> readEquationsFromFile(const std::string &input_file_path) {
    std::vector<std::string> equations;
    // Open the file stream
    std::ifstream input_file(input_file_path);
    // Check to make sure the file existed
    if (!input_file) {
        throw Exception("Could not open file: " + input_file_path);
    }
    std::string line;
    // Read the file line by line and add each line as a string to the vector of equations
    while (std::getline(input_file, line)) {
        equations.push_back(line);
    }
    return equations;
}

} // namespace io_utils
} // namespace eqeval
