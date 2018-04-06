#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>

#include "eqeval/equation_evaluator.h"
#include "eqeval/string_utils.h"
#include "eqeval/shunting_yard.h"

namespace eqeval {

EquationEvaluator::EquationEvaluator() {}

void EquationEvaluator::solve(const std::vector<std::string> &equations) {
    // store a copy of the equation strings
    equation_strings_ = std::vector<std::string>(equations);

    // Attempt to generate parsers from the each of the equation strings read from the file
    generateParsers(equations);

    int prev_num_equations_left_to_solve = 0;
    int loop_count = 0;

    // We now have parsers for all equations in the file, let's try to evaluate them
    while (!equation_parsers_.empty()) {
        // grab the first equation from the queue
        auto eq = equation_parsers_.front();
        // parse the equation string
        try {
            evaluateEquation(eq);
        } catch (const Exception &e) {
            // if we can recover (eg, variable unknown), catch the exception and
            // move the calc to the other end of the queue
            if (e.isRecoverable()) {
                // std::cerr << "Recoverable error: " << e.what() << std::endl;
                equation_parsers_.push_back(eq);
            } else {
                // non-recoverable, bubble it up
                throw e;
            }
        }
        // done processing that equation, try the next
        equation_parsers_.pop_front();

        // Check to make sure we're not continuously popping and appending in a loop
        // This is the case when there are more variables than equations
        if(prev_num_equations_left_to_solve == equation_parsers_.size()) {
            loop_count++;
        }
        prev_num_equations_left_to_solve = equation_parsers_.size();
        if(loop_count >= equations.size()) {
            throw Exception("Detected loop in solver.");
        }
    }
}

void EquationEvaluator::generateParsers(const std::vector<std::string> &equation_strings) {
    for (auto eq_str : equation_strings) {
        equation_parsers_.push_back(equation_parser::EquationParser(eq_str));
    }
}

bool EquationEvaluator::resolveVariable(const std::string &key, std::string &value) {
    if (variable_map_.find(key) == variable_map_.end()) {
        return false;
    } else {
        value = variable_map_.at(key);
        return true;
    }
}

void EquationEvaluator::evaluateEquation(equation_parser::EquationParser &eq) {
    // check for non-unique solution
    std::string dummy;
    if (resolveVariable(eq.getLHS(), dummy)) {
        throw Exception("Variable \"" + eq.getLHS() + "\" already has known solution, non-unique!");
    }
    // run shunting yard algorithm on infix rhs
    auto rpn = algorithm::shuntingYardInfixToRPN(eq.getRHSTokens(), variable_map_);
    // evaluate shunting yard sorting as result
    auto result = algorithm::rpnToULong(rpn, operator_map_);
    // update the variable map
    variable_map_.insert(std::pair<std::string, std::string>(eq.getLHS(), std::to_string(result)));
}

void EquationEvaluator::printEquations() noexcept {
    for (auto eq_str : equation_strings_) {
        std::cout << eq_str << std::endl;
    }
}

void EquationEvaluator::printSolution() noexcept {
    for (auto const &x : variable_map_) {
        std::cout << x.first << " = " << x.second << std::endl;
    }
}


} // namespace eqeval