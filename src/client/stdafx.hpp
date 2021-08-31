#pragma once

#include <initializer_list>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <ctime>
#include <mutex>

using namespace std::literals;
namespace fs = std::filesystem;

#include <Windows.h>
#include <DbgHelp.h>
#include <winuser.h>

#include <imgui.h>
#include <examples/imgui_impl_dx9.h>
#include <examples/imgui_impl_win32.h>

#include <shared/utils/version.hpp>
#include <shared/utils/utils.hpp>

#include <asmjit/core/jitruntime.h>
#include <asmjit/x86/x86assembler.h>

#include <utils/console/console.hpp>
#include <utils/hook/hook.hpp>

std::int64_t ImGui_ImplWin32_WndProcHandler(::HWND, std::uint32_t, std::uint64_t, std::int64_t);