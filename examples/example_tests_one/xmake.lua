skse_plugin({
    name = "SkyUnit Example Tests One",
    version = "0.1.0",
    author = "Mrowr Purr",
    email = "mrowr.purr@gmail.com",
    deps = {"skyunit"},
    --
    packages = {
        "SkyrimScripting.Plugin",
        "SkyrimScripting.Messages",
        "catch2",
        "nlohmann_json"
    },
    --
    src = {"*.cpp"}
})
