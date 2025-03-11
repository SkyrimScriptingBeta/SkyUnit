add_rules("mode.debug", "mode.release")

set_languages("c++23")

mod_info = {
    name = "Test plugin for ExampleStaticLibrary",
    version = "0.0.1",
    author = "Mrowr Purr",
    email = "mrowr.purr@gmail.com",
    mod_files = {"Scripts"}
}

skyrim_versions = {"ae"}

mods_folders = os.getenv("SKYRIM_MODS_FOLDERS")

if mods_folders then
    mod_info.mods_folders = mods_folders
else
    print("SKYRIM_MODS_FOLDERS environment variable not set")
end

print("Skyrim versions to build for: " .. table.concat(skyrim_versions, ", "))

for _, game_version in ipairs(skyrim_versions) do
    add_requires("skyrim-commonlib-" .. game_version)
end

for _, game_version in ipairs(skyrim_versions) do
    target("SKSE Plugin - " .. game_version:upper())
        set_basename(mod_info.name .. "-" .. game_version:upper())
        add_files("*.cpp")
        add_packages("skyrim-commonlib-" .. game_version)
        add_rules("@skyrim-commonlib-" .. game_version .. "/plugin", {
            mod_name = mod_info.name .. " (" .. game_version:upper() .. ")",
            mods_folders = mod_info.mods_folders or "",
            mod_files = mod_info.mod_files,
            name = mod_info.name,
            version = mod_info.version,
            author = mod_info.author,
            email = mod_info.email
        })
        add_deps("ExampleStaticLibrary")
end
