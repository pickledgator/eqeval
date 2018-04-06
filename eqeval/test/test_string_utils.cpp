#include "catch.hpp"
#include "eqeval/string_utils.h"

/// Set of test cases for the string utils

TEST_CASE("Test for string utils", "[string_utils]") {

    SECTION("is operator") {
        REQUIRE_FALSE(eqeval::string_utils::isOperator(std::string("blah")));
        REQUIRE_FALSE(eqeval::string_utils::isOperator(std::string("=")));
        REQUIRE(eqeval::string_utils::isOperator(std::string("+")));
        REQUIRE_FALSE(eqeval::string_utils::isOperator(std::string("3")));
        REQUIRE_FALSE(eqeval::string_utils::isOperator(std::string("two words")));
        REQUIRE_FALSE(eqeval::string_utils::isOperator(std::string(" - ")));
        REQUIRE_FALSE(eqeval::string_utils::isOperator(std::string("-")));
        REQUIRE_FALSE(eqeval::string_utils::isOperator(std::string("*")));
        REQUIRE_FALSE(eqeval::string_utils::isOperator(std::string("/")));
    }

    SECTION("is equals operator") {
        REQUIRE_FALSE(eqeval::string_utils::isEqualsOperator(std::string("blah")));
        REQUIRE_FALSE(eqeval::string_utils::isEqualsOperator(std::string("3")));
        REQUIRE_FALSE(eqeval::string_utils::isEqualsOperator(std::string("+")));
        REQUIRE_FALSE(eqeval::string_utils::isEqualsOperator(std::string("-")));
        REQUIRE(eqeval::string_utils::isEqualsOperator(std::string("=")));
    }

    SECTION("is number") {
        REQUIRE(eqeval::string_utils::isNumber(std::string("33")));
        REQUIRE_FALSE(eqeval::string_utils::isNumber(std::string("+")));
        REQUIRE_FALSE(eqeval::string_utils::isNumber(std::string("-")));
        REQUIRE_FALSE(eqeval::string_utils::isNumber(std::string("=")));
        REQUIRE_FALSE(eqeval::string_utils::isNumber(std::string("thisisaword")));
        REQUIRE_FALSE(eqeval::string_utils::isNumber(std::string("more than one word")));
    }

    SECTION("is variable") {
        REQUIRE_FALSE(eqeval::string_utils::isVariable(std::string("33")));
        REQUIRE_FALSE(eqeval::string_utils::isVariable(std::string("+")));
        REQUIRE_FALSE(eqeval::string_utils::isVariable(std::string("-")));
        REQUIRE_FALSE(eqeval::string_utils::isVariable(std::string("=")));
        REQUIRE(eqeval::string_utils::isVariable(std::string("thisisaword")));
        REQUIRE_FALSE(eqeval::string_utils::isVariable(std::string("more than one word")));
    }

    SECTION("extact tokens from string") {
        std::string lhs;
        std::vector<std::string> rhs_tokens;
        REQUIRE(eqeval::string_utils::extractTokensFromString(std::string("var = 1"), lhs, rhs_tokens));
        REQUIRE(lhs == "var");
        REQUIRE(rhs_tokens.size() == 1);
        REQUIRE(rhs_tokens[0] == "1");
        REQUIRE(eqeval::string_utils::extractTokensFromString(std::string("test = 1 + 3 + blah"), lhs, rhs_tokens));
        REQUIRE(lhs == "test");
        REQUIRE(rhs_tokens.size() == 5);
        REQUIRE(rhs_tokens[4] == "blah");
        REQUIRE_THROWS(eqeval::string_utils::extractTokensFromString(std::string("= 1 + 3 + var3"), lhs, rhs_tokens));
        REQUIRE_THROWS(
            eqeval::string_utils::extractTokensFromString(std::string("var + 1 = 3 + var"), lhs, rhs_tokens));
        REQUIRE_THROWS(eqeval::string_utils::extractTokensFromString(std::string("var ="), lhs, rhs_tokens));
        REQUIRE_THROWS(eqeval::string_utils::extractTokensFromString(std::string("var="), lhs, rhs_tokens));
        REQUIRE_NOTHROW(
            eqeval::string_utils::extractTokensFromString(std::string("var       =      1"), lhs, rhs_tokens));
        REQUIRE_THROWS(
            eqeval::string_utils::extractTokensFromString(std::string("var.       =      1"), lhs, rhs_tokens));
        REQUIRE_THROWS(
            eqeval::string_utils::extractTokensFromString(std::string("var2       =      1 + var1"), lhs, rhs_tokens));
        REQUIRE_THROWS(eqeval::string_utils::extractTokensFromString(
            std::string("var2 =      1        +     var1"), lhs, rhs_tokens));
    }

    SECTION("tokens to string") {
        std::vector<std::string> tokens = { "var", "=", "1", "+", "2" };
        std::string out = "var = 1 + 2";
        REQUIRE(eqeval::string_utils::tokensToString(tokens) == out);
    }
}