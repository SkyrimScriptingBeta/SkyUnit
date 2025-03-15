-- xmake config --build_example=y --commonlib=skyrim-commonlib-ae

add_rules("mode.release", "mode.debug")

set_languages("c++23")

add_repositories("SkyrimScripting https://github.com/SkyrimScripting/Packages.git")
add_repositories("SkyrimScriptingBeta https://github.com/SkyrimScriptingBeta/Packages.git")
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

includes("xmake/*.lua")

option("build_plugin")
    set_default(true)
    
option("build_examples")
    set_default(true)

skyrim_versions = {"ng"}

if has_config("build_plugin") then
    includes("SkyUnit.Plugin/xmake.lua")
end

if has_config("build_examples") then
    includes("ExampleTestSuites/*/xmake.lua")
end
