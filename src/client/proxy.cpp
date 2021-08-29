#include <proxy.h>
#include <initguid.h>

#include <main.hpp>

HMODULE hmod;

std::wstring SHGetKnownFolderPath(REFKNOWNFOLDERID rfid, DWORD dwFlags, HANDLE hToken)
{
    std::wstring r;
    WCHAR* szSystemPath = nullptr;
    if (SUCCEEDED(SHGetKnownFolderPath(rfid, dwFlags, hToken, &szSystemPath)))
    {
        r = szSystemPath;
    }
    CoTaskMemFree(szSystemPath);
    return r;
};

namespace proxy
{
    static LONG OriginalLibraryLoaded = 0;

    void init()
    {
        if (_InterlockedCompareExchange(&OriginalLibraryLoaded, 1, 0) != 0) return;

        std::wstring moduleFileName = GetModuleFileNameW(hmod);
        auto szSystemPath = SHGetKnownFolderPath(FOLDERID_System, 0, nullptr) + L'\\' + moduleFileName.substr(moduleFileName.find_last_of(L"/\\") + 1);

        dinput8.LoadOriginalLibrary(LoadLibraryW(&szSystemPath[0]));
    }
}

bool __stdcall DllMain(::HMODULE hModule, ::DWORD reason, ::LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        hmod = hModule;
        proxy::init();
        ddr::init();
    }
    return TRUE;
}