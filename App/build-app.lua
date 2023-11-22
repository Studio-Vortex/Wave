project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   {
      "src",

	  -- Include Wave
	  "../Wave/src"
   }

   links
   {
      "Wave"
   }

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin/int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

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