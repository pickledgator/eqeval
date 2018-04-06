#include "eqeval/equation_evaluator.h"
#include "eqeval/exception.h"
#include "eqeval/io_utils.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace {

namespace po = boost::program_options;

} // namespace

int main(int argc, char **argv) {
    // Stack storage for program options parameter
    std::string input_file_path;

    // Setup program options and specify fields
    po::options_description desc("Options");
    auto options = desc.add_options();
    options("help,h", "Display this help message")("equations-file-path,f",
        po::value<std::string>(&input_file_path)->required(), "Path to equations file (required)");

    // Create the program options variable map and parse the inputs
    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    // Ensure required command line arguments are provided
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

    // Create our mutable evaluator object
    auto ee = eqeval::EquationEvaluator();

    // Attempt to read the input file
    // In event that this fails, we won't be able to show the desired output since we haven't actually read the file.
    // This could later be replaced with a different interface, eg, read equations from a db, receive equations over a socket, etc.
    std::vector<std::string> equations;
    try {
        equations = eqeval::io_utils::readEquationsFromFile(input_file_path);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    // If we've obtained our list of equation strings, let's try to solve them!
    try {
        ee.solve(equations);
    } catch (const eqeval::Exception &e) {
        // If we catch an error during the solve, due to bad input data, an infeasible solution, or something else,
        // just print the input equations as they are read from the file.
        ee.printEquations();
        return -1;
    }

    // If the process successfully completes, display the results and exit
    ee.printSolution();

    // Done
    return 0;
}
