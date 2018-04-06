#include "catch.hpp"
#include "eqeval/shunting_yard.h"
#include <map>

TEST_CASE("Tests for shunting yard algorithm", "[shunting_yard]") {
    std::map<std::string, std::function<unsigned long(unsigned long, unsigned long)>> operator_map{ { "+",
        [](unsigned long a, unsigned long b) { return a + b; } } };

    SECTION("unknown variable") {
        std::map<std::string, std::string> variable_map;
        variable_map.insert(std::pair<std::string, std::string>("a", "3"));
        variable_map.insert(std::pair<std::string, std::string>("b", "4"));
        std::vector<std::string> tokens = {"c", "+", "3"};
        REQUIRE_THROWS(eqeval::algorithm::shuntingYardInfixToRPN(tokens, variable_map));
    }

    SECTION("valid input") {
        std::map<std::string, std::string> variable_map;
        variable_map.insert(std::pair<std::string, std::string>("a", "3"));
        variable_map.insert(std::pair<std::string, std::string>("b", "4"));
        std::vector<std::string> tokens = {"b", "+", "3"};
        auto out = eqeval::algorithm::shuntingYardInfixToRPN(tokens, variable_map);
        REQUIRE(out.size() == 3);
        REQUIRE(out[0] == "4");
        REQUIRE(out[1] == "3");
        REQUIRE(out[2] == "+");
    }

    SECTION("complex input") {
        std::map<std::string, std::string> variable_map;
        variable_map.insert(std::pair<std::string, std::string>("a", "3"));
        variable_map.insert(std::pair<std::string, std::string>("b", "4"));
        std::vector<std::string> tokens = {"b", "+", "3", "+", "a", "+", "1000"};
        auto out = eqeval::algorithm::shuntingYardInfixToRPN(tokens, variable_map);
        REQUIRE(out.size() == 7);
        REQUIRE(out[6] == "+");
    }

    SECTION("rpn to ulong valid") {
        std::vector<std::string> tokens = {"3", "4", "+"};
        REQUIRE(eqeval::algorithm::rpnToULong(tokens, operator_map) == 7);
    }

    SECTION("rpn to ulong invalid") {
        std::vector<std::string> tokens = {"3", "a", "+"};
        REQUIRE_THROWS(eqeval::algorithm::rpnToULong(tokens, operator_map));
        std::vector<std::string> tokens2 = {"3", "a", "+", "4", "+"};
        REQUIRE_THROWS(eqeval::algorithm::rpnToULong(tokens2, operator_map));
    }

    SECTION("both methods") {
        std::map<std::string, std::string> variable_map;
        variable_map.insert(std::pair<std::string, std::string>("a", "3"));
        variable_map.insert(std::pair<std::string, std::string>("b", "4"));
        std::vector<std::string> tokens = {"b", "+", "3"};
        auto out = eqeval::algorithm::shuntingYardInfixToRPN(tokens, variable_map);
        REQUIRE(eqeval::algorithm::rpnToULong(out, operator_map) == 7);
    }
}