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

    void readFile(const std::string &input_file_path);
    void printSolution() noexcept;
    void printEquations() noexcept;
    void solve();

  private:
    void generateParsers(const std::vector<std::string> &equation_strings);
    void evaluateEquation(EquationParser &eq);
    std::vector<std::string> shuntingYardSimple(const std::vector<std::string> &tokens);
    bool resolveVariable(const std::string &key, std::string &value);
    unsigned long evaluateRPN(std::vector<std::string> tokens);

    std::vector<std::string> equation_strings_;
    std::deque<EquationParser> equation_parsers_;
    std::map<std::string, std::string> variable_map_;
    std::map<std::string, std::function<unsigned long(unsigned long, unsigned long)>> operator_map_{ { "+",
        [](unsigned long a, unsigned long b) { return a + b; } } };
};

} // namespace eqeval

#endif // EQEVAL_EQUATION_EVALUATOR_HPP
