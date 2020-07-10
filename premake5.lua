workspace "Dx12_FeatureDump"

architecture "x64"
	targetdir "build"
	
	configurations 
	{ 
		"Debug", 
		"Release"
	}
		
project "Dx12Features"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/%{cfg.system}-%{cfg.buildcfg}")
	debugdir ("bin/%{cfg.system}-%{cfg.buildcfg}")
	objdir ("bin-int/%{cfg.system}-%{cfg.buildcfg}")
	targetname ("%{prj.name}-%{cfg.architecture}-%{cfg.buildcfg}")

	files 
	{ 
		"src/**.h", 
		"src/**.c", 
		"src/**.hpp", 
		"src/**.cpp" 
	}

	includedirs
	{
		"src",
	}
	
	filter "system:windows"
		systemversion "latest"
		

	filter "configurations:Debug"
		defines
		{
			"_DEBUG"
		}
		symbols "On"
				
	filter "configurations:Release"
		defines 
		{
			"NDEBUG"
		}
		optimize "On"