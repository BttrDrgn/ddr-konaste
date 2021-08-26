#include <main.hpp>

#include <utils/console/console.hpp>
#include <utils/exception/exception.hpp>
#include <utils/hook/hook.hpp>

extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 1;
extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 1;

#pragma region Proxy
struct dinput8_dll {
	HMODULE dll;
	FARPROC oDirectInput8Create;
	FARPROC oDllCanUnloadNow;
	FARPROC oDllGetClassObject;
	FARPROC oDllRegisterServer;
	FARPROC oDllUnregisterServer;
} dinput8;

extern "C" {
	FARPROC PA = 0;
	int runASM();

	void fDirectInput8Create() { PA = dinput8.oDirectInput8Create; runASM(); }
	void fDllCanUnloadNow() { PA = dinput8.oDllCanUnloadNow; runASM(); }
	void fDllGetClassObject() { PA = dinput8.oDllGetClassObject; runASM(); }
	void fDllRegisterServer() { PA = dinput8.oDllRegisterServer; runASM(); }
	void fDllUnregisterServer() { PA = dinput8.oDllUnregisterServer; runASM(); }
}

void setupFunctions() {
	dinput8.oDirectInput8Create = GetProcAddress(dinput8.dll, "DirectInput8Create");
	dinput8.oDllCanUnloadNow = GetProcAddress(dinput8.dll, "DllCanUnloadNow");
	dinput8.oDllGetClassObject = GetProcAddress(dinput8.dll, "DllGetClassObject");
	dinput8.oDllRegisterServer = GetProcAddress(dinput8.dll, "DllRegisterServer");
	dinput8.oDllUnregisterServer = GetProcAddress(dinput8.dll, "DllUnregisterServer");
}
#pragma endregion

namespace ddr
{
	void init()
	{
		utils::exception::init("client");
		utils::console::init();

		PRINT_INFO("%s", *reinterpret_cast<int*>(0x00000001401B5BC4));
	}
}

bool __stdcall DllMain(::HMODULE, ::DWORD reason, ::LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		char path[MAX_PATH];
		GetWindowsDirectory(path, sizeof(path));

		strcat_s(path, "\\system32\\dinput8.dll");
		dinput8.dll = LoadLibrary(path);
		setupFunctions();

		ddr::init();

		return true;
	}

	return false;
}
