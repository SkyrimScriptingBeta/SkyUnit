target("local-catch2-runner-by-tags")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("catch2", "nlohmann_json")