workspace "PROJECT_NAME"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    startproject "App"
    
    -- Workspace wide build options for MSVC
    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
    include "Core/build-core.lua"
group ""

include "App/build-app.lua"