#ifndef EQEVAL_STRING_UTILS_H
#define EQEVAL_STRING_UTILS_H

#include <string>

namespace eqeval {

bool isOperator(const std::string &str);
bool isEqualsOperator(const std::string &str);
bool isNumber(const std::string &str);
bool isVariable(const std::string &str);

} // namespace eqeval

#endif // EQEVAL_STRING_UTILS_H