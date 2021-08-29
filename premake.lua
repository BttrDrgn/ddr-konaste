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
		"$(DXSDK_DIR)lib\\x64\\",
		".\\deps\\drpc\\",
		".\\deps\\minhook\\bin",
	}

	includedirs {
		".\\src\\",
		"deps\\imgui\\",
		".\\deps\\drpc\\",
		".\\deps\\MinHook\\include\\",
		".\\deps\\asmjit\\src\\",
		".\\deps\\udis86\\",
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
		
		--Manifest info
		"rsc_CompanyName=\"PV\"",
		"rsc_LegalCopyright=\"MIT License\"",
		"rsc_FileVersion=\"1.0.0.0\"",
		"rsc_ProductVersion=\"1.0.0.0\"",
		"rsc_InternalName=\"%{prj.name}\"",
		"rsc_ProductName=\"%{prj.name}\"",
		"rsc_OriginalFilename=\"%{prj.name}.dll\"",
		"rsc_FileDescription=\"DDRedux Client\"",
		"rsc_UpdateUrl=\"https://github.com/BttrDrgn/ddr\"",
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
			"cd ..\\tools\\",
			"call version.bat",
		}

		postbuildcommands {
			"copy /y \"$(TargetPath)\" \"C:\\Games\\DanceDanceRevolution\\game\\modules\\\"",
		}

		dependson {
			"ImGui",
			"Discord",
			"Asmjit",
			"Udis86",
		}

		links {
			"d3d9",
			"dbghelp",
			"discord",
			"..\\deps\\drpc\\discord_game_sdk.dll.lib",
			"asmjit",
			"MinHook.x64",
			"udis86",
			"imgui",
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
		
	project "Asmjit"
		language "c++"
		kind "sharedlib"
		warnings "off"

		files {
			"deps\\asmjit\\src\\asmjit\\**.cpp",
			"deps\\asmjit\\src\\asmjit\\**.h",
		}

		includedirs {
			"deps\\asmjit\\src\\asmjit\\",
		}

	project "Udis86"
		language "c++"
		kind "staticlib"
		warnings "off"

		files {
			"deps\\udis86\\libudis86\\*.c",
			"deps\\udis86\\libudis86\\*.h",
			"deps\\extra\\udis86\\libudis86\\*.c",
			"deps\\extra\\udis86\\libudis86\\*.h",
		}

		includedirs {
			"deps\\udis86\\libudis86\\",
			"deps\\extras\\udis86\\",
			"deps\\extras\\udis86\\libudis86\\",
		}