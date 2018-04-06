#include "catch.hpp"
#include "eqeval/equation_parser.h"
#include <sstream>

/// Set of test cases for the equation parser class

TEST_CASE("Tests for equation parser", "[equation_parser]") {

    SECTION("token failure") { 
        REQUIRE_THROWS(eqeval::equation_parser::EquationParser(std::string("var ="))); 
    }

    SECTION("valid parse") {
        auto parse = eqeval::equation_parser::EquationParser(std::string("var = 1 + 2"));
        REQUIRE(parse.getLHS() == "var");
        REQUIRE(parse.getRHS() == "1 + 2");
        REQUIRE(parse.getRHSTokens().size() == 3);
        REQUIRE(parse.getRHSTokens()[1] == "+");
        std::stringstream out;
        out << parse;
        REQUIRE(out.str() == std::string("Equation(var = 1 + 2)"));
    }
}