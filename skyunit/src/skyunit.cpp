#include "skyunit.h"

#include <SkyrimScripting/Messages.h>
#include <SkyrimScripting/Plugin.h>

#include <catch2/catch_all.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <format>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>

using json = nlohmann::json;

// Custom JSON Reporter
class CustomJsonReporter : public Catch::StreamingReporterBase {
public:
    CustomJsonReporter(Catch::ReporterConfig&& config) : StreamingReporterBase(std::move(config)) {
        m_preferences.shouldRedirectStdOut      = true;
        m_preferences.shouldReportAllAssertions = false;
    }

    ~CustomJsonReporter() override {
        // Write final JSON on destruction to the stream
        m_stream << result.dump(2) << std::endl;
    }

    static std::string getDescription() { return "Custom minimal JSON reporter"; }

    void testRunStarting(Catch::TestRunInfo const&) override {
        result          = json::object();
        result["tests"] = json::array();
        counts          = {0, 0, 0, 0};
    }

    void testCaseStarting(Catch::TestCaseInfo const& testInfo) override {
        currentTest         = json::object();
        currentTest["name"] = testInfo.name;

        json tags = json::array();
        for (auto const& tag : testInfo.tags) {
            tags.push_back(tag.original);
        }
        currentTest["tags"] = tags;

        currentTest["failures"] = json::array();
        currentTestFailed       = false;
        currentTestSkipped      = false;
    }

    void assertionEnded(Catch::AssertionStats const& assertionStats) override {
        auto const& result = assertionStats.assertionResult;

        if (!result.succeeded()) {
            // Capture failure details
            json failure          = json::object();
            failure["file"]       = result.getSourceInfo().file;
            failure["line"]       = result.getSourceInfo().line;
            failure["expression"] = result.getExpression();

            if (result.hasExpandedExpression()) {
                failure["expanded"] = result.getExpandedExpression();
            }

            if (result.hasMessage()) {
                failure["message"] = result.getMessage();
            }

            failure["result_type"] = result.getResultType();

            currentTest["failures"].push_back(failure);
            currentTestFailed = true;
        }
    }

    void testCaseEnded(Catch::TestCaseStats const& testCaseStats) override {
        // Determine status
        std::string status;
        if (currentTestSkipped) {
            status = "skipped";
            counts.skipped++;
        } else if (testCaseStats.testInfo->okToFail()) {
            if (currentTestFailed) {
                status = "fail-but-ok";
                counts.failButOk++;
            } else {
                status = "passed";
                counts.passed++;
            }
        } else if (currentTestFailed) {
            status = "failed";
            counts.failed++;
        } else {
            status = "passed";
            counts.passed++;
        }

        currentTest["status"] = status;
        result["tests"].push_back(currentTest);
    }

    void skipTest(Catch::TestCaseInfo const&) override { currentTestSkipped = true; }

    void testRunEnded(Catch::TestRunStats const&) override {
        // Add summary counts
        result["summary"] = json::object({
            {"passed",      counts.passed   },
            {"failed",      counts.failed   },
            {"skipped",     counts.skipped  },
            {"fail-but-ok", counts.failButOk}
        });

        // Overall status: failed if any tests failed (excluding fail-but-ok)
        result["status"] = (counts.failed > 0) ? "failed" : "passed";
    }

private:
    json result;
    json currentTest;
    bool currentTestFailed  = false;
    bool currentTestSkipped = false;

    struct {
        int passed    = 0;
        int failed    = 0;
        int skipped   = 0;
        int failButOk = 0;
    } counts;
};

CATCH_REGISTER_REPORTER("skyunit-json", CustomJsonReporter)

void run_tests_with_tag(std::string_view tag) {
    Log("SkyUnit: Running tests with tag '{}'", tag);

    // Create a Catch2 session
    Catch::Session session;

    // Build tag filter string
    std::string tag_filter  = std::format("[{}]", tag);
    std::string output_path = json_test_result_output_path();

    // Set up command line arguments to configure reporter and filter
    const char* argv_custom[] = {"skyunit", tag_filter.c_str(), "-r", "skyunit-json", "-o", output_path.c_str()};
    int         argc_custom   = 6;

    // Apply configuration
    int returnCode = session.applyCommandLine(argc_custom, argv_custom);
    if (returnCode != 0) {
        return;
    }

    // Run the session
    session.run();
}
