#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>

#include "eqeval/equation_evaluator.h"
#include "eqeval/shunting_yard.h"
#include "eqeval/string_utils.h"

namespace eqeval {

EquationEvaluator::EquationEvaluator() {}

void EquationEvaluator::solve(const std::vector<std::string> &equations) {
    // Store a copy of the equation strings
    equation_strings_ = std::vector<std::string>(equations);

    // Attempt to generate parsers from the each of the equation strings passed as input
    generateParsers(equations);

    // Initialize counters for determining if the number if the system of equations is undeterminable
    int prev_num_equations_left_to_solve = 0;
    int loop_count = 0;

    // The parsers have organized the equation data into the appropriate tokenized representations to be solved
    while (!equation_parsers_.empty()) {
        // Grab the first equation from the queue
        auto eq = equation_parsers_.front();
        // Attempt to evaluate the individual equation
        unsigned long result;
        bool result_valid = false;
        try {
            result = evaluateEquation(eq);
            result_valid = true;
        } catch (const Exception &e) {
            // In the event that a variable is unknown, we can catch the recoverable exception and push this equation
            // to be solved later (push it onto the back of the queue). It's possible that the necessary variables needed
            // to solve this equation will be available in the solutions map after processing other equations first.
            if (e.isRecoverable()) {
                equation_parsers_.push_back(eq);
            } else {
                // If our exception is non-recoverable, bubble it up
                throw e;
            }
        }
        // Done processing that equation, remove it from the queue
        equation_parsers_.pop_front();

        // Update the variable map with the new known solution so it can be used later if needed
        // Ensure that our map contains a string representation of the result
        if(result_valid) {
            // Check for non-unique solution. If we've already solved a variable, ie, its already in our variables map
            // the solution can't be unique
            std::string variable_value;
            auto variable_exists = resolveVariable(eq.getLHS(), variable_value);
            // If we our lhs is already found in our solutions map, but the value is the same as the newly computed value
            // the solution is still unique! But if the new solution is different than the solution we already found, 
            // we'll need to throw a non-unique exception.
            if (variable_exists && variable_value != std::to_string(result)) {
                throw Exception("Variable \"" + eq.getLHS() + "\" already has known solution, non-unique!");
            }
            variable_map_.insert(std::pair<std::string, std::string>(eq.getLHS(), std::to_string(result)));
        }

        // Check to make sure we're not continuously popping and appending in a loop
        // This is the case when there are more variables than equations in the system
        if (prev_num_equations_left_to_solve == equation_parsers_.size()) {
            // If the stack size the last time through the loop is the same size as the current time through,
            // we didn't solve any equations, so keep counting.
            loop_count++;
        }
        prev_num_equations_left_to_solve = equation_parsers_.size();
        // If our loop counter grows to be the size of the number of equations, we cannot possibly solve it since we've gone
        // through every equation and didn't solve any of them. This is the worst case scenario and likely conservative since
        // it may keep trying more times than it needs to.
        if (loop_count >= equations.size()) {
            throw Exception("Detected loop in solver");
        }
    }
}

void EquationEvaluator::generateParsers(const std::vector<std::string> &equation_strings) {
    // Create parser objects for every equation string, store these in a class member variable
    for (auto eq_str : equation_strings) {
        equation_parsers_.push_back(equation_parser::EquationParser(eq_str));
    }
}

bool EquationEvaluator::resolveVariable(const std::string &key, std::string &value) {
    // Check to see if the key is in the map
    if (variable_map_.find(key) == variable_map_.end()) {
        return false;
    } else {
        // Set the value of the key as the output variable "value" if it's found
        value = variable_map_.at(key);
        return true;
    }
}

unsigned long EquationEvaluator::evaluateEquation(equation_parser::EquationParser &eq) {
    // run shunting yard algorithm on infix rhs
    auto rpn = algorithm::shuntingYardSimpleInfixToRPN(eq.getRHSTokens(), variable_map_);
    // evaluate shunting yard sorting as result
    return algorithm::rpnToULong(rpn, operator_map_);
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