workspace "Yunni"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Yunni"
	location "Yunni"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Yunni/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"YUNNI_BUILD_DLL",
			"YN_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "YN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "YN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "YN_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Yunni/src"
	}

	links
	{
		"Yunni"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"YN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "YN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "YN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "YN_DIST"
		optimize "On"
