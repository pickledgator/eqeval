#include "eqeval/shunting_yard.h"
#include "eqeval/exception.h"
#include "eqeval/string_utils.h"
#include <iostream>
#include <stack>

namespace eqeval {
namespace algorithm {

std::vector<std::string> shuntingYardInfixToRPN(
    const std::vector<std::string> &tokens, const std::map<std::string, std::string> &variable_map) {
    std::vector<std::string> output;
    std::stack<std::string> stack;
    for (auto token : tokens) {
        // if token is a number, push it to the output queue
        if (string_utils::isNumber(token)) {
            output.push_back(token);
        }
        // if the token is a variable, look up the variable in the map to resolve it
        else if (string_utils::isVariable(token)) {
            std::string value_of_variable;
            // try to resolve the variable from the map
            try {
                value_of_variable = variable_map.at(token);
            }
            // if the resolve fails, we don't know what the value of this variable is yet
            // throw an error since we can't solve the equations
            // TODO(pickledgator): May be possible to resolve this variable later, maybe we
            // can just save the equation and try again later?
            catch (const std::exception &e) {
                throw Exception("Variable \"" + token + "\" unknown at time of use", true);
            }
            output.push_back(value_of_variable);
        }

        else if (string_utils::isOperator(token)) {
            if (!stack.empty()) {
                auto top_of_stack = stack.top();
                // the only check that applies to this project is checking for an operator of equal
                // precedence. The other checks are ignored but can be implemented later to extend this
                // Other checks:
                // there is a function at the top of the operator stack
                // there is an operator at the top of the operator stack with greater precedence
                // the operator at the top of the operator stack has equal precedence and is left associative
                // the operator at the top of the operator stack is not a left bracket
                while (string_utils::isOperator(top_of_stack) && top_of_stack == token) {
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

        else {
            throw Exception("Unknown character as token: " + token);
        }
    }

    // we've iterated through all tokens, if there are still tokens on the stack, pop them on to the output queue
    while (!stack.empty()) {
        output.push_back(stack.top());
        stack.pop();
    }

    return output;
}

unsigned long rpnToULong(const std::vector<std::string> &tokens,
    const std::map<std::string, std::function<unsigned long(unsigned long, unsigned long)>> &operator_map) {
    std::stack<std::string> stack;

    for (auto token : tokens) {
        // if the next token is an operator, assume we are ready to calculate
        if (string_utils::isOperator(token)) {
            auto var2 = std::stoul(stack.top().c_str(), nullptr, 0);
            stack.pop();
            auto var1 = std::stoul(stack.top().c_str(), nullptr, 0);
            stack.pop();
            // Use the operator map to evaluate the calculation
            unsigned long result;
            try {
                result = operator_map.at(token)(var1, var2);
            }
            catch(const std::exception &e) {
                throw Exception("Exception in operator map application: var1=" + std::to_string(var1) + " var2=" + std::to_string(var2));
            }
            // push the result back onto the stack for the next token
            stack.push(std::to_string(result));
        }
        // if the next token is not an operator, add it to the stack
        else {
            stack.push(token);
        }
    }
    // grab the final result from the top of the stack
    auto final_result = std::stoul(stack.top().c_str(), nullptr, 0);
    stack.pop();
    return final_result;
}

} // namespace eqeval
} // namespace algorithm
