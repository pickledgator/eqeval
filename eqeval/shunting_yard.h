#ifndef EQEVAL_SHUNTING_YARD_H
#define EQEVAL_SHUNTING_YARD_H

#include <string>
#include <vector>
#include <map>

namespace eqeval {
namespace algorithm {

    std::vector<std::string> shuntingYardInfixToRPN(
        const std::vector<std::string> &tokens, const std::map<std::string, std::string> &variable_map);
    unsigned long rpnToULong(const std::vector<std::string> &tokens, const std::map<std::string, std::function<unsigned long(unsigned long, unsigned long)>> &operator_map);

} // namespace algorithm
} // namespace eqeval

#endif // EQEVAL_SHUNTING_YARD_H