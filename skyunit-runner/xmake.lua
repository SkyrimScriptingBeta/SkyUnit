skse_plugin({
    name = "SkyUnit Runner",
    version = "0.1.0",
    author = "Mrowr Purr",
    email = "mrowr.purr@gmail.com",
    packages = {
        "SkyrimScripting.Plugin",
        "SkyrimScripting.Messages",
        "nlohmann_json"
    },
    src = {"src/**.cpp"}
})
