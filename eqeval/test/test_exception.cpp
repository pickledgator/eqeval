#include "catch.hpp"
#include "eqeval/exception.h"

TEST_CASE("Tests for exceptions", "[exceptions]") {

    SECTION("recoverable") {
        auto e = eqeval::Exception("recoverable message", true);
        REQUIRE(e.what() == std::string("recoverable message"));
        REQUIRE(e.isRecoverable() == true);
    }

    SECTION("non-recoverable") {
        auto e = eqeval::Exception("non-recoverable message");
        REQUIRE(e.what() == std::string("non-recoverable message"));
        REQUIRE(e.isRecoverable() == false);
        auto e2 = eqeval::Exception("non-recoverable message", false);
        REQUIRE(e.isRecoverable() == false);
    }

}