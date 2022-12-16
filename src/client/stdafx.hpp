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

#include <shared/utils/version.hpp>
#include <shared/utils/utils.hpp>

#include <asmjit/core/jitruntime.h>
#include <asmjit/x86/x86assembler.h>

#include <utils/console/console.hpp>
#include <utils/hook/hook.hpp>
