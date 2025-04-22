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
IncludeDir["Glad"] = "LearningEngine/ThirdParty/Glad/include"
IncludeDir["ImGui"] = "LearningEngine/ThirdParty/ImGui"
IncludeDir["glm"] = "LearningEngine/ThirdParty/glm"

group "Dependencies"

	include "LearningEngine/ThirdParty/GLFW"
	include "LearningEngine/ThirdParty/Glad"
	include "LearningEngine/ThirdParty/ImGui"
group ""

project "LearningEngine"
	location "LearningEngine"
	kind "SharedLib"
	language "C++"
	buildoptions "/utf-8"
	staticruntime "off"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "LEpch.h"
	pchsource "LearningEngine/Source/LEpch.cpp"

	files
	{
		"%{prj.name}/Source/**.h", 
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/ThirdParty/glm/glm/**.hpp",
		"%{prj.name}/ThirdParty/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/ThirdParty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LE_PLATFORM_WINDOWS",
			"LE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			--("IF NOT EXISTS ../Binaries/" ..outputdir.. "${prj.name} mkdir ../Binaries/" ..outputdir.. "${prj.name}"),
			-- TODO: clean build (delete Binaries) fails here, figure out why
			("{COPYFILE} %{cfg.buildtarget.relpath} \"../Binaries/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "LE_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "LE_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "LE_DISTRIBUTION"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	buildoptions "/utf-8"
	staticruntime "off"

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
		"LearningEngine/Source",
		"%{IncludeDir.glm}"
	}

	links
	{
		"LearningEngine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LE_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "LE_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Distribution"
		defines "LE_DISTRIBUTION"
		runtime "Release"
		optimize "On"
