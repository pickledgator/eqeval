#ifndef EQEVAL_EQUATION_PARSER_HPP
#define EQEVAL_EQUATION_PARSER_HPP

#include <iostream>
#include <string>
#include <vector>

namespace eqeval {
namespace equation_parser {

class EquationParser {
  public:
    EquationParser(const std::string &str);
    std::string getLHS() const { return lhs_str_; };
    std::string getRHS() const { return rhs_str_; };
    std::vector<std::string> const &getRHSTokens() { return rhs_tokens_; };

  private:
    std::string raw_str_;
    std::string lhs_str_;
    std::string rhs_str_;
    std::vector<std::string> rhs_tokens_;
};

std::ostream &operator<<(std::ostream &strm, const EquationParser &a);

} // namespace equation_parser
} // namespace eqeval

#endif // EQEVAL_EQUATION_PARSER_HPP