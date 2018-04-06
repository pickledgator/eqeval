#ifndef EQEVAL_STRING_UTILS_H_
#define EQEVAL_STRING_UTILS_H_

#include <string>
#include <vector>

namespace eqeval {
namespace string_utils {

/// Set of simple-operation string utilities that are used throughout the library.

/// Tests if the input string is considered an operator. Operators include: "+", "-", "*", "/"
bool isOperator(const std::string &str);

/// Tests if the input string is specifically the "=" operator
bool isEqualsOperator(const std::string &str);

/// Tests if the input string is a number using ::isdigit
bool isNumber(const std::string &str);

/// Tests if the input string contains only alpha characters
bool isVariable(const std::string &str);

/* Extracts tokenized elements from an input string
 * For example, consider the input string "3 + 4 + 5"
 * The method would return true if the output variable rhs_tokens is populated with the following:
 * ["3", "+", "4", "+", "5"]
 * @param str input string to extract tokens from
 * @param rhs_tokens output reference populated with tokens on success
 * @returns true is tokens are extracted successfully, otherwise false
 * @throws eqeval::Exception()
 */
bool extractTokensFromString(const std::string &str, std::string &lhs, std::vector<std::string> &rhs_tokens);

/// Re-assembles a string from a set of token strings
std::string tokensToString(const std::vector<std::string> &tokens);

} // namespace string_utils
} // namespace eqeval

#endif // EQEVAL_STRING_UTILS_H_