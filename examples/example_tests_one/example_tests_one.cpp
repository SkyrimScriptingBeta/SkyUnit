#include <skyunit.h>

UNIT_TEST("This is unit test one") { CHECK(1 + 1 == 2); }

DATA_TEST("This is data test one") {
    std::string str = "hello";
    CHECK(str.size() == 5);
}
