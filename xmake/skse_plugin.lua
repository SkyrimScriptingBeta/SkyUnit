function skse_plugin(mod_info)
    local mods_folders = os.getenv("SKYRIM_MODS_FOLDERS")

    local mod_info_defaults = {
        version = "0.0.1",
        author = "Mrowr Purr",
        email = "mrowr.purr@gmail.com"
    }

    mod_info.version = mod_info.version or mod_info_defaults.version
    mod_info.author = mod_info.author or mod_info_defaults.author
    mod_info.email = mod_info.email or mod_info_defaults.email
    mod_info.mod_files = mod_info.mod_files or mod_info_defaults.mod_files

    if mods_folders then
        mod_info.mods_folders = mods_folders
    else
        print("SKYRIM_MODS_FOLDERS environment variable not set")
    end

    print("Skyrim versions to build for: " .. table.concat(skyrim_versions, ", "))

    for _, game_version in ipairs(skyrim_versions) do
        add_requires("skyrim-commonlib-" .. game_version)
        add_requires("SkyrimScripting.Plugin", { configs = {
            commonlib = "skyrim-commonlib-" .. game_version,
            use_log_library = true,
            use_skyrimscripting_logging = true,
            use_skse_plugin_info_library = true
        }})
    end

    for _, game_version in ipairs(skyrim_versions) do
        target("SKSE Plugin - " .. mod_info.name .. " - " .. game_version:upper())
            set_basename((mod_info.basename or mod_info.name) .. "-" .. game_version:upper())
            add_files("*.cpp")
            add_packages("skyrim-commonlib-" .. game_version)
            add_rules("@skyrim-commonlib-" .. game_version .. "/plugin", {
                mod_name = mod_info.name .. " (" .. game_version:upper() .. ")",
                mods_folders = mod_info.mods_folders or "",
                mod_files = mod_info.mod_files or {},
                name = mod_info.name,
                version = mod_info.version,
                author = mod_info.author,
                email = mod_info.email
            })
            for _, dep in ipairs(mod_info.deps or {}) do
                add_deps(dep)
            end
            for _, package in ipairs(mod_info.packages or {}) do
                add_packages(package)
            end
            add_packages("SkyrimScripting.Plugin", { configs = {
                commonlib = "skyrim-commonlib-" .. game_version,
                use_log_library = true,
                use_skyrimscripting_logging = true,
                use_skse_plugin_info_library = true
            }})
    end
end
