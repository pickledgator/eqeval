#include "eqeval/string_utils.h"
#include "eqeval/exception.h"
#include <sstream>
#include <string>

namespace eqeval {
namespace string_utils {

    bool isOperator(const std::string &str) { return str == "+" || str == "-" || str == "*" || str == "/"; };

    bool isEqualsOperator(const std::string &str) { return str == "="; };

    bool isNumber(const std::string &str) {
        auto res = std::find_if(str.begin(), str.end(), [](char c) { return !std::isdigit(c); });
        return !str.empty() && res == str.end();
    };

    bool isVariable(const std::string &str) {
        auto res = std::find_if(str.begin(), str.end(), [](char c) { return !std::isalpha(c); });
        return !str.empty() && res == str.end();
    };

    bool extractTokensFromString(const std::string &str, std::string &lhs, std::vector<std::string> &rhs_tokens) {
        std::istringstream iss(str);
        std::vector<std::string> all_tokens;
        std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
            std::back_inserter(all_tokens));

        if (all_tokens.size() < 3) {
            throw Exception("Expected at least 3 tokens in string");
        }

        // The first element must be a variable, otherwise, throw
        if (!isVariable(all_tokens[0])) {
            throw Exception("First token is not a variable! " + all_tokens[0]);
        }
        // save the variable name of the left hand side
        lhs = all_tokens[0];

        // The second element must be an "=" operator
        // No need to save this, just verify it exists in the correct spot in the string
        if (!isEqualsOperator(all_tokens[1])) {
            throw Exception("The second token must be \"=\"! " + all_tokens[1]);
        }

        // The rest of the string starting at index = 2 will be our RHS expression
        // The tokens populated here are in infix order
        rhs_tokens = std::vector<std::string>(&all_tokens[2], &all_tokens[all_tokens.size()]);
        return true;
    }

    std::string tokensToString(const std::vector<std::string> &tokens) {
        std::string str;
        // reconstruct without whitespace
        for (auto token : tokens) {
            str.append(token);
        }
        return str;
    }

} // namespace string_utils
} // namespace eqeval