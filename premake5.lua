workspace "DV2556Project"
    location "Build"
    configurations { "Debug", "Release"}
    architecture "x86"

    filter "system:windows"
        systemversion "latest"

    staticruntime "on"
    filter "configurations:Debug"
        defines {"_DEBUG"}
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        optimize "on"
        runtime "Release"

    project "DV2556Project"
        kind "ConsoleApp"
        language "C++"
        targetdir "Bin/%{cfg.buildcfg}"
        files { "Source/**.*" }

        vpaths {
            ["Headers/"] = { "**.h", "**.hpp" },
            ["Sources/"] = {"**.c", "**.cpp"}
        }