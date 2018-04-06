#ifndef EQEVAL_EQUATION_EVALUATOR_H
#define EQEVAL_EQUATION_EVALUATOR_H

#include <deque>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "eqeval/equation_parser.h"
#include "eqeval/exception.h"

namespace eqeval {

class EquationEvaluator {
  public:
    EquationEvaluator();
    void printSolution() noexcept;
    void printEquations() noexcept;
    void solve(const std::vector<std::string> &equations);
    std::map<std::string, std::string> const &getSolution() { return variable_map_; };

  private:
    void generateParsers(const std::vector<std::string> &equation_strings);
    void evaluateEquation(equation_parser::EquationParser &eq);
    // std::vector<std::string> shuntingYardSimple(const std::vector<std::string> &tokens);
    bool resolveVariable(const std::string &key, std::string &value);
    // unsigned long evaluateRPN(std::vector<std::string> tokens);

    std::vector<std::string> equation_strings_;
    std::deque<equation_parser::EquationParser> equation_parsers_;
    std::map<std::string, std::string> variable_map_;
    std::map<std::string, std::function<unsigned long(unsigned long, unsigned long)>> operator_map_{ { "+",
        [](unsigned long a, unsigned long b) { return a + b; } } };
};

} // namespace eqeval

#endif // EQEVAL_EQUATION_EVALUATOR_HPP
