#include <SkyrimScripting/Messages.h>
#include <SkyrimScripting/Plugin.h>

#include <catch2/catch_all.hpp>

#define UNIT_TEST(name) TEST_CASE(name, "[skyunit][unit]")
#define DATA_TEST(name) TEST_CASE(name, "[skyunit][data]")
#define INTEGRATION_TEST(name) TEST_CASE(name, "[skyunit][integration]")

constexpr auto SkyUnitRunnerMessage   = "SkyUnit Runner";
constexpr auto TestResultOutputFolder = "Data/SKSE/Plugins/SkyUnit/TestResults";

inline const std::unordered_map<std::string, std::string> RunCommandsToTestTags = {
    {"run-unit-tests",        "unit"       },
    {"run-data-tests",        "data"       },
    {"run-integration-tests", "integration"}
};

inline const auto json_test_result_output_path() { return std::format("{}/{}.json", TestResultOutputFolder, SKSEPluginInfo::GetPluginName()); }

void run_tests_with_tag(std::string_view tag);

_SKSEPlugin_Entrypoint_(SkyUnit) {
    Log("SkyUnit: Initializing SkyUnit plugin.");
    SkyrimScripting::SKSE_Messages::ListenForMessagesFromAll();
    Log("SkyUnit: SkyUnit plugin initialized.");
}

_SKSEPlugin_OnMessage_(SkyUnit)(SKSE::MessagingInterface::Message* message) {
    Log("SkyUnit: Received message from sender '{}'", message->sender);
    SkyrimScripting::Messages::HandleMessage(message->sender, message);
};

_OnMessage_(SkyUnit)(SkyrimScripting::Messages::Message* message) {
    if (!message->sender_equals(SkyUnitRunnerMessage)) return;
    for (const auto& [command, tag] : RunCommandsToTestTags) {
        if (message->text_equals(command)) {
            run_tests_with_tag(tag);
            break;
        }
    }
    Log("SkyUnit: Completed running tests for command '{}'. Results written to '{}'.", message->text(), json_test_result_output_path());
};