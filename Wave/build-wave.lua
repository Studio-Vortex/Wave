project "Wave"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files
   {
      "src/**.h",
      "src/**.cpp",
      
      "%{prj.name}/vendor/miniaudio/miniaudio.h",
   }

   includedirs
   {
      "src",
      "vendor",
   }

   targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../bin/int/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "WAVE_DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "WAVE_RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "WAVE_DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"