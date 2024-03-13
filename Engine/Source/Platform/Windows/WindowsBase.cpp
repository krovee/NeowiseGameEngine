#include <Platform/Windows/WindowsBase.h>

#if NW_OS(WIN32)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Base/Diagnostics.h>


namespace Neowise::Platform::Windows {

	namespace {
		PFNWindowMessageProc _Proc;
		LRESULT MSPROC(::HWND hWnd, ::UINT Msg, ::WPARAM wParam, ::LPARAM lParam) {
			if (_Proc) {
				SWindowEventData ev = {};
				bool jump = false;

				switch (Msg) {
					case WM_CLOSE: ev.type = E_WINDOW_EVENT_CLOSE; jump = true; break;
					case WM_DESTROY: ev.type = E_WINDOW_EVENT_QUIT; jump = true; break;
					case WM_SIZE: {
						ev.type = E_WINDOW_EVENT_RESIZE;
						ev.onResize.width = LOWORD(lParam);
						ev.onResize.height = HIWORD(lParam);
						jump = true;
					} break;
					case WM_SETFOCUS: {
						ev.type = E_WINDOW_EVENT_ENTER_FOCUS;
						jump = true;
					} break;
					case WM_KILLFOCUS: {
						ev.type = E_WINDOW_EVENT_EXIT_FOCUS;
						jump = true;
					} break;
					case WM_SYSKEYDOWN:
					case WM_KEYDOWN: {
						ev.type = E_WINDOW_EVENT_KEY_PRESSED;
						jump = true;
						ev.onKey.evk = (EVirtualKey)wParam;
						ev.onKey.isPressed = true;
					} break;
					case WM_SYSKEYUP:
					case WM_KEYUP: {
						ev.type = E_WINDOW_EVENT_KEY_RELEASED;
						jump = true;
						ev.onKey.evk = (EVirtualKey)wParam;
						ev.onKey.isPressed = false;
					} break;
					case WM_CHAR: {
						ev.type = E_WINDOW_EVENT_CHAR;
						jump = true;
					} break;
					case WM_LBUTTONDOWN:
					case WM_RBUTTONDOWN:
					case WM_MBUTTONDOWN:
					case WM_XBUTTONDOWN: {
						ev.type = E_WINDOW_EVENT_MOUSE_PRESSED;
						jump = true;
					} break;
					case WM_LBUTTONUP:
					case WM_RBUTTONUP:
					case WM_MBUTTONUP:
					case WM_XBUTTONUP: {
						ev.type = E_WINDOW_EVENT_MOUSE_RELEASED;
						jump = true;
					} break;
					case WM_MOUSEMOVE: {
						ev.type = E_WINDOW_EVENT_MOUSE_MOVE;
						const auto p = MAKEPOINTS(lParam);
						ev.onMouseMove.x = p.x;
						ev.onMouseMove.y = p.y;
						jump = true;
					} break;
					case WM_MOVE: {
						ev.type = E_WINDOW_EVENT_MOVE;
						ev.onMove = { LOWORD(lParam), HIWORD(lParam) };
						jump = true;
					} break;
				}

				if (jump) {
					_Proc((Windows::HWND)hWnd, ev);
				}
			}
			return DefWindowProc(hWnd, Msg, wParam, lParam);
		}
	}

	HINSTANCE getCurrentPlatformHandle(void) {
		return HINSTANCE(::GetModuleHandle(nullptr));
	}

	HANDLE getProcessHeap(void) {
		static const auto v = ::GetProcessHeap();
		return v;
	}

	LPVOID heapAlloc(HANDLE hHeap, uint64 size, HeapAllocFlags flags) {
		DWORD dwFlags = 0;
		if ((flags & E_HEAP_ALLOC_FLAGS_ZERO_INITIALIZED) == E_HEAP_ALLOC_FLAGS_ZERO_INITIALIZED) {
			dwFlags = HEAP_ZERO_MEMORY;
		}
		return ::HeapAlloc(hHeap, dwFlags, size);
	}

	void heapFree(HANDLE hHeap, void* p) {
		::HeapFree(hHeap, NULL, p);
	}

	DWORD getLastError(void) {
		return GetLastError();
	}

	DWORD getLastErrorStringA(char* s) {
		LPVOID lpMsgBuf = nullptr;
		DWORD dw = GetLastError();

		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&lpMsgBuf, 0, NULL);

		const auto len = LocalSize(lpMsgBuf);
		memcpy(s, lpMsgBuf, len);
		LocalFree(lpMsgBuf);

		return DWORD(len);
	}

	DWORD getLastErrorStringW(wchar_t* s) {
		// Retrieve the system error message for the last-error code

		LPVOID lpMsgBuf = nullptr;
		DWORD dw = GetLastError();

		FormatMessageW(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&lpMsgBuf, 0, NULL);

		const auto len = LocalSize(lpMsgBuf);
		memcpy(s, lpMsgBuf, len);
		LocalFree(lpMsgBuf);

		return DWORD(len);
	}
	
	LPVOID copyMemory(LPVOID dst, LPVOID src, uint64 size) {
		return memcpy(dst, src, size);
	}

	LPVOID fillMemory(LPVOID dst, int32 value, uint64 size) {
		return memset(dst, value, size);
	}

	bool compareMemory(CLPVOID p1, CLPVOID p2, uint64 size) {
		return memcmp(p1, p2, size) == 0;
	}

	uint64 lstrlenA(const char* s) {
		return uint64(::lstrlenA(s));
	}
	
	uint64 lstrlenW(const wchar_t* s) {
		return uint64(::lstrlenW(s));
	}
	
	void getKeyboardState(uint8 state[256]) {
		(void)::GetKeyboardState((uint8*)state);
	}

	BOOL allocConsole(void) {
		return ::AllocConsole();
	}

	void freeConsole(void) {
		FreeConsole();
	}

	HANDLE getStdOutHandle(void) {
		static const auto v = ::GetStdHandle(STD_OUTPUT_HANDLE);
		return v;
	}

	void writeConsoleA(HANDLE hConsole, const char* text) {
		WriteConsoleA(hConsole, text, ::lstrlenA(text), NULL, NULL);
	}

	void writeConsoleW(HANDLE hConsole, const wchar_t* text) {
		WriteConsoleW(hConsole, text, ::lstrlenW(text), NULL, NULL);
	}

	void writeConsoleA(HANDLE hConsole, const char* text, uint64 len) {
		WriteConsoleA(hConsole, text, (::DWORD)len, NULL, NULL);
	}

	void writeConsoleW(HANDLE hConsole, const wchar_t* text, uint64 len) {
		WriteConsoleW(hConsole, text, (::DWORD)len, NULL, NULL);
	}

	HWND getConsoleWindow(void) {
		static const auto v = (Windows::HWND)::GetConsoleWindow();
		return v;
	}

	HWND createWindowW(const wchar_t* title, int32 x, int32 y, int32 w, int32 h, WindowFlags flags, PFNWindowMessageProc proc) {
		_Proc = proc;
		
		WNDCLASSEXW wcex = { sizeof(WNDCLASSEXW) };
		wcex.lpszClassName = title;
		wcex.lpfnWndProc = MSPROC;
		wcex.hInstance = GetModuleHandleW(nullptr);
		wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wcex.hIconSm = wcex.hIcon;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		
		RegisterClassExW(&wcex);

		const DWORD dwStyle = flags;
		DWORD showCmd = SW_SHOW;

		if (w == getPrimaryMonitorWidth() && h == getPrimaryMonitorHeight()) {
			showCmd = SW_MAXIMIZE;
		}

		x = ((int32)getPrimaryMonitorWidth() / 2) - (w / 2);
		y = ((int32)getPrimaryMonitorHeight() / 2) - (h / 2);

		RECT rc = { 0, 0, w, h };
		AdjustWindowRect((LPRECT)&rc, dwStyle, FALSE);

		w = rc.right - rc.left;
		h = rc.bottom - rc.top;

		auto hWnd = CreateWindowExW(NULL, title, title, dwStyle, x, y, w, h, NULL, NULL, NULL, NULL);
		NW_ASSERT(hWnd, "Failed to create window for some strange reason..");
		
		ShowWindow(hWnd, showCmd);
		UnregisterClassW(title, wcex.hInstance);

		return (Windows::HWND)hWnd;
	}

	HWND createWindowA(const char* title, int32 x, int32 y, int32 w, int32 h, WindowFlags flags, PFNWindowMessageProc proc) {
		_Proc = proc;

		WNDCLASSEXA wcex = { sizeof(WNDCLASSEXA) };
		wcex.lpszClassName = title;
		wcex.lpfnWndProc = MSPROC;
		wcex.hInstance = GetModuleHandleA(nullptr);
		wcex.hIcon = LoadIconA(nullptr, MAKEINTRESOURCEA(32512));
		wcex.hIconSm = wcex.hIcon;
		wcex.hCursor = LoadCursorA(nullptr, MAKEINTRESOURCEA(32512));

		RegisterClassExA(&wcex);

		const DWORD dwStyle = flags;
		DWORD showCmd = SW_SHOW; 

		if (w == getPrimaryMonitorWidth() && h == getPrimaryMonitorHeight()) {
			showCmd = SW_MAXIMIZE;
		}

		x = ((int32)getPrimaryMonitorWidth() / 2) - (w / 2);
		y = ((int32)getPrimaryMonitorHeight() / 2) - (h / 2);

		RECT rc = { 0, 0, w, h };
		AdjustWindowRect((LPRECT)&rc, dwStyle, FALSE);

		w = rc.right - rc.left;
		h = rc.bottom - rc.top;

		auto hWnd = CreateWindowExA(NULL, title, title, dwStyle, x, y, w, h, NULL, NULL, NULL, NULL);
		if (hWnd) {
			ShowWindow(hWnd, showCmd);
		}
		
		UnregisterClassA(title, wcex.hInstance);

		return (Windows::HWND)hWnd;
	}

	void destroyWindow(HWND hWnd) {
		DestroyWindow((::HWND)hWnd);
		hWnd = NULL;
	}

	void setWindowLongPtrW(HWND hWnd, WindowLongPtrName name, ptraddr ptraddress) {
		SetWindowLongPtrW((::HWND)hWnd, name, ptraddress);
	}

	void setWindowLongPtrA(HWND hWnd, WindowLongPtrName name, ptraddr ptraddress) {
		SetWindowLongPtrA((::HWND)hWnd, name, ptraddress);
	}

	ptraddr getWindowLongPtrW(HWND hWnd, WindowLongPtrName name) {
		return GetWindowLongPtrW((::HWND)hWnd, name);
	}

	ptraddr getWindowLongPtrA(HWND hWnd, WindowLongPtrName name) {
		return GetWindowLongPtrA((::HWND)hWnd, name);
	}

	void setWindowTextA(HWND hWnd, const char* text) {
		SetWindowTextA((::HWND)hWnd, text);
	}

	void setWindowTextW(HWND hWnd, const wchar_t* text) {
		SetWindowTextW((::HWND)hWnd, text);
	}

	void showWindow(HWND hWnd, WindowShowFlags flags) {
		ShowWindow((::HWND)hWnd, flags);
	}

	BOOL peekWindowMessagesA(HWND hWnd) {
		::MSG msg;
		while (PeekMessageA(&msg, (::HWND)hWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		return true;
	}

	BOOL peekWindowMessagesW(HWND hWnd) {
		::MSG msg;
		while (PeekMessageW(&msg, (::HWND)hWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		return true;
	}

	uint64 getPrimaryMonitorWidth(void) {
		static const auto v = GetSystemMetrics(SM_CXSCREEN);
		return v;
	}

	uint64 getPrimaryMonitorHeight(void) {
		static const auto v = GetSystemMetrics(SM_CYSCREEN);
		return v;
	}

	void sleep(DWORD dwMilliseconds) {
		Sleep(dwMilliseconds);
	}

	void queryPerformanceFrequency(int64& freq) {
		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	}

	void queryPerformanceCounter(int64& cnt) {
		QueryPerformanceCounter((LARGE_INTEGER*)&cnt);
	}

	void exitProcess(uint32 code) {
		ExitProcess(code);
	}

	void breakProcess(void) {
		DebugBreak();
	}

	void outputDebugStringA(const char* str) {
		OutputDebugStringA(str);
	}

	void outputDebugStringW(const wchar_t* str) {
		OutputDebugStringW(str);
	}

	HANDLE createThread(void(*pfnStartProc)(void*), void* params, DWORD* pId) {
		if (!pfnStartProc) {
			return (HANDLE)THREAD_HANDLE_INVALID;
		}

		auto h = CreateThread(NULL, 1048576, (LPTHREAD_START_ROUTINE)pfnStartProc, params, CREATE_SUSPENDED, (::DWORD*)&pId);
		NW_ASSERT(h != NULL, "Failed to spawn win32 thread!");

		return h;
	}

	DWORD resumeThread(HANDLE hThread) {
		return ResumeThread(hThread);
	}

	void closeHandle(HANDLE handle) {
		CloseHandle(handle);
	}

	void getExitCodeThread(HANDLE hThread, DWORD* pExitcode) {
		GetExitCodeThread(hThread, pExitcode);
	}

	void terminateThread(HANDLE hThread, DWORD exitcode) {
		(void)TerminateThread(hThread, exitcode);
	}

	EWaitResult waitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) {
		return (EWaitResult)WaitForSingleObject(hHandle, dwMilliseconds);
	}

	uint interlockValue(volatile uint* pValue) {
		return InterlockedCompareExchange(pValue, 1, 0);
	}

}

#endif
