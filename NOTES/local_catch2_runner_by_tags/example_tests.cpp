#include <catch2/catch_all.hpp>

TEST_CASE("Example passing test1", "[tag1]") { REQUIRE(1 + 1 == 2); }

TEST_CASE("Example passing test2", "[tag2]") { REQUIRE(1 + 1 == 2); }
TEST_CASE("Example failing test2", "[tag2]") { REQUIRE(2 * 2 == 5); }
TEST_CASE("Another passing test2", "[tag2]") {
    REQUIRE(1 + 1 == 2);
    REQUIRE(2 + 2 == 4);
    REQUIRE(3 + 3 == 6);
}
TEST_CASE("Skipped test2", "[tag2]") {
    SKIP("Skipping this test intentionally");
    REQUIRE(0 == 1);
}
