#include <catch2/catch_all.hpp>

int main(int argc, char* argv[]) {
    // Run tests with specific tags

    // Create a Catch2 session
    Catch::Session session;

    // Set up command line arguments to configure reporter and filter
    const char* argv_custom[] = {"test", "[tag2]", "-r", "custom-json", "-o", "test-results.json"};
    int argc_custom = 6;

    // Apply configuration
    int returnCode = session.applyCommandLine(argc_custom, argv_custom);
    if (returnCode != 0) {
        return returnCode;
    }

    // Run the session
    int result = session.run();

    return result;
}