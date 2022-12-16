workspace "DDR"
	location "./build/"

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/"
	objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}/"
	buildlog "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}.log"

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "mbcs"
	architecture "x64"
	warnings "extra"

	syslibdirs {
		"$(DXSDK_DIR)lib/x64/",
		"./deps/minhook/bin",
	}

	includedirs {
		"./src/",
		"./deps/MinHook/include/",
		"./deps/asmjit/src/",
		"./deps/udis86/",
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
		optimize "full"
		runtime "release"
		symbols "on"

	project "client"
		kind "sharedlib"
		targetname "dinput8"
		cppdialect "C++17"

		language "c++"
		kind "sharedlib"
		warnings "off"
		
		pchheader "stdafx.hpp"
		pchsource "src/client/stdafx.cpp"
		forceincludes "stdafx.hpp"
		
		prebuildcommands {
			"cd ../tools/",
			"call version.bat",
		}

		postbuildcommands {
			"copy /y \"$(TargetPath)\" \"C:/Games/DanceDanceRevolution/game/modules/\"",
		}
		
		defines {
			--Manifest info
			"rsc_FileDescription=\"DDRedux Client\"",
			"rsc_UpdateUrl=\"https://github.com/BttrDrgn/ddr\"",
		}

		dependson {
			"ImGui",
			"Asmjit",
			"Udis86",
		}

		links {
			"dbghelp",
			"asmjit",
			"MinHook.x64",
			"udis86",
		}
		
		files {
			"./src/client/**",
			"./src/shared/**",
		}

		includedirs {
			"./src/client/",
			"./src/shared/",
		}

	group "Dependencies"
		
	project "Asmjit"
		targetname "asmjit"
		language "c++"
		kind "sharedlib"
		warnings "off"
		
--[[	Switch to static building asmjit at some point so we don't have to ship as many dlls


		kind "staticlib"
		defines {
			"ASMJIT_STATIC",
		}
]]--

		files {
			"deps/asmjit/src/asmjit/**.cpp",
			"deps/asmjit/src/asmjit/**.h",
		}

		includedirs {
			"deps/asmjit/src/asmjit/",
		}

	project "Udis86"
		language "c++"
		kind "staticlib"
		warnings "off"

	    files {
            "deps/udis86/libudis86/*.c",
            "deps/udis86/libudis86/*.h",
			"deps/extras/udis86/itab.h",
			"deps/extras/udis86/itab.c",
        }
        includedirs {
            "deps/udis86/libudis86/",
			"deps/extras/udis86/",
        }