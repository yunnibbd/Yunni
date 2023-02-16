workspace "Yunni"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories reletive to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Yunni/vendor/GLFW/include"
IncludeDir["Glad"] = "Yunni/vendor/Glad/include"
IncludeDir["ImGui"] = "Yunni/vendor/imgui"
IncludeDir["glm"] = "Yunni/vendor/glm"

include "Yunni/vendor/GLFW"
include "Yunni/vendor/Glad"
include "Yunni/vendor/imgui"

project "Yunni"
	location "Yunni"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ynpch.h"
	pchsource "Yunni/src/ynpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
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
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"YUNNI_BUILD_DLL",
			"YN_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "YN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "YN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "YN_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Yunni/vendor/spdlog/include",
		"Yunni/src",
		"Yunni/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Yunni"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"YN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "YN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "YN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "YN_DIST"
		runtime "Release"
		optimize "on"
