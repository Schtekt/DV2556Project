solution "DV2556Project"
    configurations { "Debug", "Release" }
    location "Build"
        
    project "DV2556Project"
    kind "ConsoleApp"
    language "C++"
    targetdir "Bin/%{cfg.buildcfg}"
    files { "Source/**.*" }
    vpaths {
        ["Headers/"] = { "**.h", "**.hpp" },
        ["Sources/"] = {"**.c", "**.cpp"}
    }