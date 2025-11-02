#include <catch2/catch_all.hpp>

TEST_CASE("Example passing test1", "[tag1]") { REQUIRE(1 + 1 == 2); }

TEST_CASE("Example passing test2", "[tag2]") { REQUIRE(1 + 1 == 2); }
TEST_CASE("Example failing test2", "[tag2]") { REQUIRE(2 * 2 == 5); }
