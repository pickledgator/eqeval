#include "eqeval/equation_parser.h"
#include "eqeval/exception.h"
#include "eqeval/string_utils.h"

namespace eqeval {
namespace equation_parser {

EquationParser::EquationParser(const std::string &str) : raw_str_(str) {
    auto res = string_utils::extractTokensFromString(str, lhs_str_, rhs_tokens_);
    if (!res) {
        throw Exception("Error parsing equation");
    }
    rhs_str_ = string_utils::tokensToString(rhs_tokens_);
}

std::ostream &operator<<(std::ostream &strm, const EquationParser &a) {
    return strm << "Equation(" << a.getLHS() << " = " << a.getRHS() << ")";
}

} // namespace equation_parser
} // namespace eqeavl