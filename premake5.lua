workspace "LearningEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{ 
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "LearningEngine/ThirdParty/GLFW/include"

include "LearningEngine/ThirdParty/GLFW"

project "LearningEngine"
	location "LearningEngine"
	kind "SharedLib"
	language "C++"
	buildoptions "/utf-8"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "LEpch.h"
	pchsource "LearningEngine/Source/LEpch.cpp"

	files
	{
		"%{prj.name}/Source/**.h", 
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/ThirdParty/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LE_PLATFORM_WINDOWS",
			"LE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../Binaries/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines
		{
			"LE_DEBUG",
			"LE_ENABLE_ASSERTS"
		}
		symbols "On"
		
	filter "configurations:Release"
		defines "LE_RELEASE"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "LE_DISTRIBUTION"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	buildoptions "/utf-8"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h", 
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"LearningEngine/ThirdParty/spdlog/include",
		"LearningEngine/Source"
	}

	links
	{
		"LearningEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LE_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "LE_RELEASE"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "LE_DISTRIBUTION"
		optimize "On"
