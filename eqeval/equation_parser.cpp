#include "eqeval/equation_parser.h"
#include "eqeval/string_utils.h"
#include "eqeval/exception.h"

#include <sstream>

namespace eqeval {

EquationParser::EquationParser(const std::string &str)
    : raw_str_(str) {
    extractTokens();
    rhs_str_ = tokensToString(rhs_tokens_);
}

void EquationParser::extractTokens() {
    std::istringstream iss(raw_str_);
    std::vector<std::string> all_tokens;
    std::copy(
        std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(all_tokens));

    if (all_tokens.size() < 3) {
        throw Exception("Expected at least 3 tokens in string");
    }

    // The first element must be a variable, otherwise, throw
    if (!isVariable(all_tokens[0])) {
        throw Exception("First token is not a variable! " + all_tokens[0]);
    }
    // save the variable name of the left hand side
    lhs_str_ = all_tokens[0];

    // The second element must be an "=" operator
    // No need to save this, just verify it exists in the correct spot in the string
    if (!isEqualsOperator(all_tokens[1])) {
        throw Exception("The second token must be \"=\"! " + all_tokens[1]);
    }

    // The rest of the string starting at index = 2 will be our RHS expression
    // The tokens populated here are in infix order
    rhs_tokens_ = std::vector<std::string>(&all_tokens[2], &all_tokens[all_tokens.size()]);
}

std::string EquationParser::tokensToString(const std::vector<std::string> &tokens) {
    std::string str;
    // removes spaces
    for (auto token : tokens) {
        str.append(token);
    }
    return str;
}

std::ostream &operator<<(std::ostream &strm, const EquationParser &a) {
    return strm << "Equation(" << a.getLHS() << " = " << a.getRHS() << ")";
}

} // namespace eqeavl