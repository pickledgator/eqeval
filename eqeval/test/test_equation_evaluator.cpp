#include "catch.hpp"
#include "eqeval/equation_evaluator.h"
#include <sstream>

TEST_CASE("Tests for equation evaluator", "[equation_evaluator]") {
    auto ee = eqeval::EquationEvaluator();

    SECTION("simple solve") {
        std::vector<std::string> equations = { "var = 1 + 2", "a = var + 3 + 4" };
        REQUIRE_NOTHROW(ee.solve(equations));
        REQUIRE(ee.getSolution().size() == 2);
        REQUIRE(ee.getSolution().at("var") == "3");
        REQUIRE(ee.getSolution().at("a") == "10");
    }

    SECTION("out of order solve") {
        std::vector<std::string> equations = { "var = 1 + 2", "a = var + 3 + 4", "c = var + b", "b = 1" };
        REQUIRE_NOTHROW(ee.solve(equations));
        REQUIRE(ee.getSolution().size() == 4);
        REQUIRE(ee.getSolution().at("var") == "3");
        REQUIRE(ee.getSolution().at("b") == "1");
        REQUIRE(ee.getSolution().at("c") == "4");
        REQUIRE_THROWS(ee.getSolution().at("d"));
    }

    SECTION("non-unique error") {
        std::vector<std::string> equations = { "var = 1 + 2", "a = var + 3 + 4", "var = 1 + 2 + b", "b = 1" };
        REQUIRE_THROWS(ee.solve(equations));
    }

    SECTION("double var") {
        std::vector<std::string> equations = { "var = 1 + 2", "a = a + 3 + 4" };
        REQUIRE_THROWS(ee.solve(equations));
    }

    SECTION("not enough info") {
        std::vector<std::string> equations = { "var = b + 2", "a = 3 + 4" };
        REQUIRE_THROWS(ee.solve(equations));
    }

    SECTION("bad parse") {
        std::vector<std::string> equations = { "var = ", "a = 3 + 4" };
        REQUIRE_THROWS(ee.solve(equations));
    }
}