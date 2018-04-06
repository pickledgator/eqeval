#include "eqeval/equation_evaluator.h"
#include "eqeval/exception.h"
#include "eqeval/io_utils.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace {

namespace po = boost::program_options;

} // namespace

int main(int argc, char **argv) {
    std::string input_file_path;

    po::options_description desc("Options");
    auto options = desc.add_options();
    options("help,h", "Display this help message")("equations-file-path,f",
        po::value<std::string>(&input_file_path)->required(), "Path to equations file (required)");

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    try {
        po::store(parsed, vm);
        po::notify(vm);

    } catch (boost::program_options::required_option &e) {
        std::cerr << "Missing required option" << std::endl;
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    auto ee = eqeval::EquationEvaluator();

    // Attempt to read the input file
    // In event that this fails, we won't be able to show the desired output since we haven't actually read the file.
    // Just throw an error for now.
    std::vector<std::string> equations;
    try {
        equations = eqeval::io_utils::readEquationsFromFile(input_file_path);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    // If the file is read successfully, process it.
    try {
        ee.solve(equations);
    } catch (const eqeval::Exception &e) {
        // caught an exception in processing, display input data
        ee.printEquations();
        return -1;
    }

    // If the process successfully completes, display the results
    ee.printSolution();

    // Done

    return 0;
}
