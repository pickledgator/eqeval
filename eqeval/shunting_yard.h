#ifndef EQEVAL_SHUNTING_YARD_H_
#define EQEVAL_SHUNTING_YARD_H_

#include <map>
#include <string>
#include <vector>

namespace eqeval {
namespace algorithm {

    std::vector<std::string> shuntingYardInfixToRPN(
        const std::vector<std::string> &tokens, const std::map<std::string, std::string> &variable_map);
    unsigned long rpnToULong(const std::vector<std::string> &tokens,
        const std::map<std::string, std::function<unsigned long(unsigned long, unsigned long)>> &operator_map);

} // namespace algorithm
} // namespace eqeval

#endif // EQEVAL_SHUNTING_YARD_H_