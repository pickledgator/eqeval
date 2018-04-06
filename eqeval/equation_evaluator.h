#ifndef EQEVAL_EQUATION_EVALUATOR_H_
#define EQEVAL_EQUATION_EVALUATOR_H_

#include <deque>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "eqeval/equation_parser.h"
#include "eqeval/exception.h"

namespace eqeval {

/* Evaluates a system of equations using methods that classifies the equation strings as tokens, identifies 
 * the order of operations for the equations, and evaluates the unknown variables.
 * Example equation: var = 1 + 3 + var2
 * 
 * Currently, the solver uses a shunting yard algorithm to convert the tokenized strings into postfix form
 * as reverse polish notation (RPN), and then evaluates the RPN representation from left to right. As the system of
 * equations is solved, variables are saved in a map such that they can used later in other equations as needed.
 */
class EquationEvaluator {
  public:
    /// Constructor for evalulator class
    EquationEvaluator();
    /// Print the solution to stdout
    void printSolution() noexcept;
    /// Print the input equations to stdout
    void printEquations() noexcept;
    /// Evaluate the system of equations with input argument as a vector of strings
    void solve(const std::vector<std::string> &equations);
    /// Return a reference to the solution map that contains variables as keys
    std::map<std::string, std::string> const &getSolution() { return variable_map_; };

  private:
    /// Creates eqeval::EquationParser objects for each of the equation strings in the input arguement vector
    /// Stores the new vector of parsers within the class member equation_parsers_
    void generateParsers(const std::vector<std::string> &equation_strings);
    
    /// Evalulate a single equation, as provided by the input argument parser object for that equation
    /// This method runs the shunting yard algorithm and populates the variable_map_ as the solution, if found.
    /// @throws eqeval::Exception if no solution can be found
    unsigned long evaluateEquation(equation_parser::EquationParser &eq);

    /// Checks to see if a variable exists and has a solution in our solutions map
    /// @param key input variable name
    /// @param value output reference to value of variable in map, if found
    /// @returns true if variable was found, false if not
    bool resolveVariable(const std::string &key, std::string &value);

    /// A list of equations represented by strings to solve
    std::vector<std::string> equation_strings_;
    /// A double ended queue of equation parsers left to solve
    std::deque<equation_parser::EquationParser> equation_parsers_;
    /// A map of known variables and their solutions
    std::map<std::string, std::string> variable_map_;
    /// Operator map that relates specific operators to known lambda functions that can be applied where that
    /// operator is used
    std::map<std::string, std::function<unsigned long(unsigned long, unsigned long)>> operator_map_{ { "+",
        [](unsigned long a, unsigned long b) { return a + b; } } };
};

} // namespace eqeval

#endif // EQEVAL_EQUATION_EVALUATOR_H_
