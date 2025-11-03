target("skyunit")
    set_kind("static")
    add_files("src/*.cpp")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", { public = true })
    add_packages(
        "skyrim-commonlib-ae",
        "SkyrimScripting.Plugin",
        "SkyrimScripting.Messages",
        "catch2",
        "nlohmann_json",
        { public = true }
    )
    