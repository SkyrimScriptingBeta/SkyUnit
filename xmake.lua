-- xmake config --build_example=y --commonlib=skyrim-commonlib-ae

add_rules("mode.release", "mode.debug")

set_languages("c++23")

-- Define an option for CommonLib (so users can override it)
option("commonlib")
    set_default(nil)
    set_showmenu(true)
    set_description("Which CommonLib package to use")
option_end()

option("build_example")
    set_description("Enable development tools (not installed with the package)")
    set_default(false) -- This ensures it is OFF unless explicitly enabled
option_end()

includes("ExampleStaticLibrary/xmake.lua")

if has_config("build_example") then
    print("Building example")
    -- includes("papyrus.lua")
    includes("skse.lua")
end
