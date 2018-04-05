#ifndef EQEVAL_EQUATION_STRING_PARSER_H
#define EQEVAL_EQUATION_STRING_PARSER_H

#include <iostream>
#include <string>
#include <vector>

namespace eqeval {
namespace equation_parser {

class EquationStringParser : EquationParser {
  public:
    EquationStringParser();

  private:
    void parse() override;
};

} // namespace equation_parser
} // namespace eqeval

#endif // EQEVAL_EQUATION_STRING_PARSER_H