workspace "DDR"
	location ".\\build\\"

	targetdir "%{wks.location}\\bin\\%{cfg.buildcfg}\\"
	objdir "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}\\"
	buildlog "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}.log"

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "mbcs"
	architecture "x64"
	warnings "extra"

	syslibdirs {
		".\\deps\\drpc\\",
		".\\deps\\minhook\\bin"
	}

	includedirs {
		".\\src\\",
		"deps\\imgui\\",
		".\\deps\\drpc\\",
		".\\deps\\MinHook\\include\\",
		".\\deps\\asmjit\\src\\",
	}

	flags {
		"noincrementallink",
		"shadowedvariables",
		"undefinedidentifiers",
		"multiprocessorcompile",
	}

	defines {
		"NOMINMAX",
		"WIN32_LEAN_AND_MEAN",
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
	}

	platforms {
		"x64",
	}

	configurations {
		"Release",
		"Debug",
	}	

	
	configuration "Release"
		defines "NDEBUG"
		optimize "full"
		runtime "release"
		symbols "off"

	configuration "Debug"
		defines "DEBUG"
		optimize "debug"
		runtime "debug"
		symbols "on"

	project "client"
		targetname "dinput8"
		cppdialect "C++17"

		language "c++"
		kind "sharedlib"
		warnings "off"
		
		pchheader "stdafx.hpp"
		pchsource "src/client/stdafx.cpp"
		forceincludes "stdafx.hpp"
		
		prebuildcommands {
			--"cd ..\\tools\\",
			--"call version.bat",
		}

		postbuildcommands {
			"copy /y \"$(TargetPath)\" \"C:\\Games\\DanceDanceRevolution\\game\\modules\\\"",
		}

		dependson {
			"ImGui",
			"Discord",
			"AsmJIT",
		}

		links {
			"dbghelp",
			"discord",
			"..\\deps\\drpc\\discord_game_sdk.dll.lib",
			"asmjit",
			"MinHook.x64",
		}
		
		files {
			".\\src\\client\\**",
			".\\src\\shared\\**",
		}

		includedirs {
			".\\src\\client\\",
			".\\src\\shared\\",
		}
		
	group "Dependencies"
		
	project "ImGui"
		targetname "imgui"

		language "c++"
		kind "staticlib"

		files {
			"deps\\imgui\\*.h",
			"deps\\imgui\\*.cpp",
			"deps\\imgui\\examples\\imgui_impl_dx9.h",
			"deps\\imgui\\examples\\imgui_impl_dx9.cpp",
			"deps\\imgui\\examples\\imgui_impl_win32.h",
			"deps\\imgui\\examples\\imgui_impl_win32.cpp",
		}

		includedirs {
			"deps\\imgui",
			"deps\\imgui\\examples",
		}
		
	project "Discord"
		targetname "discord"

		language "c++"
		kind "staticlib"

		files {
			"deps\\drpc\\*.h",
			"deps\\drpc\\*.cpp",
		}

		includedirs {
			"deps\\drpc",
			"deps\\drpc\\examples",
		}
		
	project "AsmJIT"
		targetname "asmjit"

		language "c++"
		kind "staticlib"
		warnings "off"

		defines {
			"ASMJIT_STATIC",
		}

		files {
			"deps\\asmjit\\src\\asmjit\\**.cpp",
		}

		includedirs {
			"deps\\asmjit\\src\\asmjit\\",
		}
