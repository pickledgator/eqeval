#ifndef EQEVAL_EQUATION_PARSER_H_
#define EQEVAL_EQUATION_PARSER_H_

#include <iostream>
#include <string>
#include <vector>

namespace eqeval {
namespace equation_parser {

/// Container for a parsed equation containing various representations of the underlying data
class EquationParser {
  public:
    /// Constructor for the class, accepts an equation string as input argument
    EquationParser(const std::string &str);
    /// Returns the left hand side of the equation as a string after parse
    std::string getLHS() const { return lhs_str_; };
    /// Returns the right hand side of the equation as a string after parse
    std::string getRHS() const { return rhs_str_; };
    /// Returns the right hand side of the equation as a vector of strings (tokens) after parse
    std::vector<std::string> const &getRHSTokens() { return rhs_tokens_; };

  private:
    std::string raw_str_;
    std::string lhs_str_;
    std::string rhs_str_;
    std::vector<std::string> rhs_tokens_;
};

/// Friend operator for serializing the contents of an EquationParser
std::ostream &operator<<(std::ostream &strm, const EquationParser &a);

} // namespace equation_parser
} // namespace eqeval

#endif // EQEVAL_EQUATION_PARSER_H_