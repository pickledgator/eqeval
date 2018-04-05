#include "eqeval/string_utils.h"
#include <string>

namespace eqeval {

bool isOperator(const std::string &str) { return str == "+"; };
bool isEqualsOperator(const std::string &str) { return str == "="; };
bool isNumber(const std::string &str) {
    auto res = std::find_if(str.begin(), str.end(), [](char c) { return !std::isdigit(c); });
    return !str.empty() && res == str.end();
};
bool isVariable(const std::string &str) { return !isOperator(str) && !isNumber(str); };

} // namespace eqeval