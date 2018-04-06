#include "catch.hpp"
#include "eqeval/io_utils.h"

/// Set of test cases for the io utils

TEST_CASE("Test for io utils", "[io_utils]") {

    SECTION("read file from disk") {
        auto equations = eqeval::io_utils::readEquationsFromFile("eqeval/test/test_equations_valid.txt");
        REQUIRE(equations.size() == 7);
    }

    SECTION("read invalid file from disk") {
        auto equations = eqeval::io_utils::readEquationsFromFile("eqeval/test/test_equations_invalid.txt");
        REQUIRE(equations.size() == 5);
    }

    SECTION("read non existent file from disk") { 
        REQUIRE_THROWS(eqeval::io_utils::readEquationsFromFile("blah.txt")); 
    }
}