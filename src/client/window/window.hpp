#pragma once

class window final
{
public:
    static void init();

	static ::HWND hwnd;
	static ::WNDPROC wnd_proc;
};