#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>

#include "eqeval/equation_evaluator.h"
#include "eqeval/string_utils.h"

namespace eqeval {

EquationEvaluator::EquationEvaluator() {}

void EquationEvaluator::solve() {
    // Attempt to generate parsers from the each of the equation strings read from the file
    generateParsers(equation_strings_);

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
    }
}

void EquationEvaluator::generateParsers(const std::vector<std::string> &equation_strings) {
    for (auto eq_str : equation_strings) {
        equation_parsers_.push_back(EquationParser(eq_str));
    }
}

void EquationEvaluator::evaluateEquation(EquationParser &eq) {
    // check for non-unique solution
    std::string dummy;
    if (resolveVariable(eq.getLHS(), dummy)) {
        throw Exception("Variable \"" + eq.getLHS() + "\" already has known solution, non-unique!");
    }
    // run shunting yard algorithm on infix rhs
    auto rpn = shuntingYardSimple(eq.getRHSTokens());
    // evaluate shunting yard sorting as result
    auto result = evaluateRPN(rpn);
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

void EquationEvaluator::readFile(const std::string &input_file_path) {
    std::ifstream input_file(input_file_path);
    if (!input_file) {
        throw std::runtime_error{ "Could not open file: " + input_file_path };
    }
    std::string line;
    while (std::getline(input_file, line)) {
        equation_strings_.push_back(line);
    }
}

bool EquationEvaluator::resolveVariable(const std::string &key, std::string &value) {
    if (variable_map_.find(key) == variable_map_.end()) {
        return false;
    } else {
        value = variable_map_[key];
        return true;
    }
}

std::vector<std::string> EquationEvaluator::shuntingYardSimple(const std::vector<std::string> &tokens) {

    std::vector<std::string> output;
    std::stack<std::string> stack;
    for (auto token : tokens) {
        // if token is a number, push it to the output queue
        if (isNumber(token)) {
            output.push_back(token);
        }
        // if the token is a variable, look up the variable in the map to resolve it
        if (isVariable(token)) {
            std::string value_of_variable;
            // try to resolve the variable from the map
            if (resolveVariable(token, value_of_variable)) {
                output.push_back(value_of_variable);
            }
            // if the resolve fails, we don't know what the value of this variable is yet
            // throw an error since we can't solve the equations
            // TODO(pickledgator): May be possible to resolve this variable later, maybe we
            // can just save the equation and try again later?
            else {
                throw Exception("Variable \"" + token + "\" unknown at time of use", true);
            }
        }

        if (isOperator(token)) {
            if (!stack.empty()) {
                auto top_of_stack = stack.top();
                // the only check that applies to this project is checking for an operator of equal
                // precedence. The other checks are ignored but can be implemented later to extend this
                // Other checks:
                // there is a function at the top of the operator stack
                // there is an operator at the top of the operator stack with greater precedence
                // the operator at the top of the operator stack has equal precedence and is left associative
                // the operator at the top of the operator stack is not a left bracket
                while (isOperator(top_of_stack) && top_of_stack == token) {
                    // pop off the operator and add it to the output queue
                    stack.pop();
                    output.push_back(top_of_stack);
                    // repeat to ensure the next operator doesn't also satisfy the constraint
                    if (!stack.empty()) {
                        top_of_stack = stack.top();
                    }
                    // if the operator stack is empty, break the loop
                    else {
                        break;
                    }
                }
            }
            // push the token onto the operator stack
            stack.push(token);
        }
    }

    // we've iterated through all tokens, if there are still tokens on the stack, pop them on to the output queue
    while (!stack.empty()) {
        output.push_back(stack.top());
        stack.pop();
    }

    return output;
}

unsigned long EquationEvaluator::evaluateRPN(std::vector<std::string> tokens) {
    std::stack<std::string> stack;

    for (auto token : tokens) {
        // if the next token is an operator, assume we are ready to calculate
        if (isOperator(token)) {
            auto var2 = std::strtoul(stack.top().c_str(), NULL, 0);
            stack.pop();
            auto var1 = std::strtoul(stack.top().c_str(), NULL, 0);
            stack.pop();
            // Use the operator map to evaluate the calculation
            auto result = operator_map_[token](var1, var2);
            // push the result back onto the stack for the next token
            stack.push(std::to_string(result));
        }
        // if the next token is not an operator, add it to the stack
        else {
            stack.push(token);
        }
    }
    // grab the final result from the top of the stack
    auto final_result = std::strtoul(stack.top().c_str(), NULL, 0);
    stack.pop();
    return final_result;
}

} // namespace eqeval