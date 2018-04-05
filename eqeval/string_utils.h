#ifndef EQEVAL_STRING_UTILS_H
#define EQEVAL_STRING_UTILS_H

#include <string>
#include <vector>

namespace eqeval {
namespace string_utils {

    bool isOperator(const std::string &str);
    bool isEqualsOperator(const std::string &str);
    bool isNumber(const std::string &str);
    bool isVariable(const std::string &str);
    bool extractTokensFromString(const std::string &str, std::string &lhs, std::vector<std::string> &rhs_tokens);
    std::string tokensToString(const std::vector<std::string> &tokens);

} // namespace string_utils
} // namespace eqeval

#endif // EQEVAL_STRING_UTILS_H