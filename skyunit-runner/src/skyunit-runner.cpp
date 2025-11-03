#include <SkyrimScripting/Messages.h>
#include <SkyrimScripting/Plugin.h>

// TODO: on post post load before kicking things off find out about the available tests from a registry

constexpr auto Message_RunUnitTests        = "run-unit-tests";
constexpr auto Message_RunDataTests        = "run-data-tests";
constexpr auto Message_RunIntegrationTests = "run-integration-tests";

SKSEPlugin_OnPostPostLoad {
    Log("SkyUnit: Broadcasting message to run unit tests.");
    SkyrimScripting::Messages::Broadcast(Message_RunUnitTests);
}

SKSEPlugin_OnDataLoaded {
    Log("SkyUnit: Broadcasting message to run data tests.");
    SkyrimScripting::Messages::Broadcast(Message_RunDataTests);
}

// TODO: integration ones :)
