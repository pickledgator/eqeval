#ifndef EQEVAL_SHUNTING_YARD_H_
#define EQEVAL_SHUNTING_YARD_H_

#include <map>
#include <string>
#include <vector>

namespace eqeval {
namespace algorithm {

/* Parses a mathematical expression provided in infix notation
 * The shunting yard algorithms helps us sort the tokenized RHS by order of operations.
 * Currently, since only "+" operators are supported, the order of operations is always trivial, but the structure
 * of this algorithm is able to be extended to support all operators (*,/,-) and parenthesis ().
 * 
 * This version of shunting yard is considered simple because it does not include logic for precedence or associativity
 * of operators since only one operator ("+") is needed. 
 * Reference design from: https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 *
 * @param tokens The tokenized RHS elements of the equation
 * @param variable_map Known solutions to variables that have already been solved
 * @returns A vector of strings with the tokens ordred in postfix (RPN) notation
 * @throws eqeval::Exception with recoverable or nonrecoverable flag
 */
std::vector<std::string> shuntingYardSimpleInfixToRPN(
    const std::vector<std::string> &tokens, const std::map<std::string, std::string> &variable_map);

/* Evaluates a mathematical expression provided in postfix (RPN) notation
 * After an expression has been tokenized and the order of operations has been solved by shunting yard,
 * we can iterate through using a stack and execute the appropriate mathematical operator on the tokens.
 * 
 * Reference design from: https://en.wikipedia.org/wiki/Reverse_Polish_notation
 *
 * @param tokens The tokenized RHS elements of the equation in RPN notation
 * @param operator_map A map between an operator character and a function that takes two input variables
 *                     and applies that operator.
 * @returns unsigned long Result of evaluation of the equation
 * @throws eqeval::Exception with recoverable or nonrecoverable flag
 */
unsigned long rpnToULong(const std::vector<std::string> &tokens,
    const std::map<std::string, std::function<unsigned long(unsigned long, unsigned long)>> &operator_map);

} // namespace algorithm
} // namespace eqeval

#endif // EQEVAL_SHUNTING_YARD_H_