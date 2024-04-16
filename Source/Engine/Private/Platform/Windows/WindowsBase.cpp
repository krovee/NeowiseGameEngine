#include <Platform/Windows/WindowsBase.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Base/Diagnostics.h>
#include <Base/DynamicLibrary.h>

#include <Engine/VulkanRHI/Common.h>
#include <Engine/VulkanRHI/API/vk_platform.h>
#include <Engine/VulkanRHI/API/vulkan_core.h>

using VkWin32SurfaceCreateFlagsKHR = VkFlags;

typedef struct VkWin32SurfaceCreateInfoKHR {
    VkStructureType                 sType;
    const void*                     pNext;
    VkWin32SurfaceCreateFlagsKHR    flags;
    HINSTANCE                       hinstance;
    HWND                            hwnd;
} VkWin32SurfaceCreateInfoKHR;

namespace Neowise::Platform::Windows {

    namespace {
        PFNWindowMessageProc _Proc;
        LRESULT MSPROC(::HWND hWnd, ::UINT Msg, ::WPARAM wParam, ::LPARAM lParam) {
            if (_Proc) {
                SWindowEventData ev = {};
                TBool jump = kFalse;

                switch (Msg) {
                    case WM_CLOSE: ev.type = E_WINDOW_EVENT_CLOSE; jump = kTrue; break;
                    case WM_DESTROY: ev.type = E_WINDOW_EVENT_QUIT; jump = kTrue; break;
                    case WM_SIZE: {
                        ev.type = E_WINDOW_EVENT_RESIZE;
                        ev.onResize.width = LOWORD(lParam);
                        ev.onResize.height = HIWORD(lParam);
                        jump = kTrue;
                    } break;
                    case WM_SETFOCUS: {
                        ev.type = E_WINDOW_EVENT_ENTER_FOCUS;
                        jump = kTrue;
                    } break;
                    case WM_KILLFOCUS: {
                        ev.type = E_WINDOW_EVENT_EXIT_FOCUS;
                        jump = kTrue;
                    } break;
                    case WM_SYSKEYDOWN:
                    case WM_KEYDOWN: {
                        ev.type = E_WINDOW_EVENT_KEY_PRESSED;
                        jump = kTrue;
                        ev.onKey.evk = (EVirtualKey)wParam;
                        ev.onKey.isPressed = kTrue;
                    } break;
                    case WM_SYSKEYUP:
                    case WM_KEYUP: {
                        ev.type = E_WINDOW_EVENT_KEY_RELEASED;
                        jump = kTrue;
                        ev.onKey.evk = (EVirtualKey)wParam;
                        ev.onKey.isPressed = kFalse;
                    } break;
                    case WM_CHAR: {
                        ev.type = E_WINDOW_EVENT_CHAR;
                        jump = kTrue;
                    } break;
                    case WM_LBUTTONDOWN:
                    case WM_RBUTTONDOWN:
                    case WM_MBUTTONDOWN:
                    case WM_XBUTTONDOWN: {
                        ev.type = E_WINDOW_EVENT_MOUSE_PRESSED;
                        ev.onMouse.evk = (EVirtualKey)wParam;
                        ev.onMouse.isPressed = kTrue;
                        jump = kTrue;
                    } break;
                    case WM_LBUTTONUP:
                    case WM_RBUTTONUP:
                    case WM_MBUTTONUP:
                    case WM_XBUTTONUP: {
                        ev.type = E_WINDOW_EVENT_MOUSE_RELEASED;
                        if (Msg == WM_LBUTTONUP) {
                            ev.onMouse.evk = (EVirtualKey)MK_LBUTTON;
                        }
                        else if (Msg == WM_RBUTTONUP) {
                            ev.onMouse.evk = (EVirtualKey)MK_RBUTTON;
                        }
                        else if (Msg == WM_MBUTTONUP) {
                            ev.onMouse.evk = (EVirtualKey)MK_MBUTTON;
                        }
                        ev.onMouse.isPressed = kFalse;
                        jump = kTrue;
                    } break;
                    case WM_MOUSEMOVE: {
                        ev.type = E_WINDOW_EVENT_MOUSE_MOVE;
                        const auto p = MAKEPOINTS(lParam);
                        ev.onMouseMove.x = p.x;
                        ev.onMouseMove.y = p.y;
                        jump = kTrue;
                    } break;
                    case WM_MOVE: {
                        ev.type = E_WINDOW_EVENT_MOVE;
                        ev.onMove = { LOWORD(lParam), HIWORD(lParam) };
                        jump = kTrue;
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

    LPVOID heapAlloc(HANDLE hHeap, TUint64 size, HeapAllocFlags flags) {
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
    
    LPVOID copyMemory(LPVOID dst, LPVOID src, TUint64 size) {
        return memcpy(dst, src, size);
    }

    LPVOID fillMemory(LPVOID dst, TInt32 value, TUint64 size) {
        return memset(dst, value, size);
    }

    TBool compareMemory(CLPVOID p1, CLPVOID p2, TUint64 size) {
        return memcmp(p1, p2, size) == 0;
    }

    TUint64 lstrlenA(const char* s) {
        return TUint64(::lstrlenA(s));
    }
    
    TUint64 lstrlenW(const wchar_t* s) {
        return TUint64(::lstrlenW(s));
    }
    
    void getKeyboardState(TUint8 state[256]) {
        (void)::GetKeyboardState((TUint8*)state);
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

    void writeConsoleA(HANDLE hConsole, const char* text, TUint64 len) {
        WriteConsoleA(hConsole, text, (::DWORD)len, NULL, NULL);
    }

    void writeConsoleW(HANDLE hConsole, const wchar_t* text, TUint64 len) {
        WriteConsoleW(hConsole, text, (::DWORD)len, NULL, NULL);
    }

    HWND getConsoleWindow(void) {
        static const auto v = (Windows::HWND)::GetConsoleWindow();
        return v;
    }

    HWND createWindowW(const wchar_t* title, TInt32 x, TInt32 y, TInt32 w, TInt32 h, WindowFlags flags, PFNWindowMessageProc proc) {
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

        x = ((TInt32)getPrimaryMonitorWidth() / 2) - (w / 2);
        y = ((TInt32)getPrimaryMonitorHeight() / 2) - (h / 2);

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

    HWND createWindowA(const char* title, TInt32 x, TInt32 y, TInt32 w, TInt32 h, WindowFlags flags, PFNWindowMessageProc proc) {
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

        x = ((TInt32)getPrimaryMonitorWidth() / 2) - (w / 2);
        y = ((TInt32)getPrimaryMonitorHeight() / 2) - (h / 2);

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

    void setWindowLongPtrW(HWND hWnd, WindowLongPtrName name, TPtrAddr ptraddress) {
        SetWindowLongPtrW((::HWND)hWnd, name, ptraddress);
    }

    void setWindowLongPtrA(HWND hWnd, WindowLongPtrName name, TPtrAddr ptraddress) {
        SetWindowLongPtrA((::HWND)hWnd, name, ptraddress);
    }

    TPtrAddr getWindowLongPtrW(HWND hWnd, WindowLongPtrName name) {
        return GetWindowLongPtrW((::HWND)hWnd, name);
    }

    TPtrAddr getWindowLongPtrA(HWND hWnd, WindowLongPtrName name) {
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
        return kTrue;
    }

    BOOL peekWindowMessagesW(HWND hWnd) {
        ::MSG msg;
        while (PeekMessageW(&msg, (::HWND)hWnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        return kTrue;
    }

    void *createVulkanSurface(VkInstance instance, HWND hWnd) {
        VkSurfaceKHR surfaceKHR = VK_NULL_HANDLE;

        using PFN_vkCreateWin32SurfaceKHR = 
            VkResult(*)(VkInstance, const VkWin32SurfaceCreateInfoKHR*, const VkAllocationCallbacks*, VkSurfaceKHR*);

        auto vkLib = ::Neowise::CDynamicLibrary::load(NW_VK_LIBRARY_NAME);
        NW_ASSERT(vkLib, "Failed to load Vulkan dynamic provider (missing " NW_VK_LIBRARY_NAME ")");

        PFN_vkGetInstanceProcAddr
            vkGetInstanceProcAddr = vkLib->getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");

        auto vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR");
        NW_ASSERT(vkCreateWin32SurfaceKHR, "Failed to load function vkCreateWin32SurfaceKHR!");

        VkWin32SurfaceCreateInfoKHR surfaceCI = { (VkStructureType)VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR };
        surfaceCI.hinstance = GetModuleHandle(NULL);
        surfaceCI.hwnd = (::HWND)hWnd;

        RHIVKFN(vkCreateWin32SurfaceKHR(instance, &surfaceCI, nullptr, &surfaceKHR), 
            "Failed to create win32 surface!");

        return surfaceKHR;
    }

    TUint64 getPrimaryMonitorWidth(void) {
        static const auto v = GetSystemMetrics(SM_CXSCREEN);
        return v;
    }

    TUint64 getPrimaryMonitorHeight(void) {
        static const auto v = GetSystemMetrics(SM_CYSCREEN);
        return v;
    }

    void sleep(DWORD dwMilliseconds) {
        Sleep(dwMilliseconds);
    }

    void queryPerformanceFrequency(TInt64& freq) {
        QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    }

    void queryPerformanceCounter(TInt64& cnt) {
        QueryPerformanceCounter((LARGE_INTEGER*)&cnt);
    }

    void exitProcess(TUint32 code) {
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

    TUint interlockValue(volatile TUint* pValue) {
        return InterlockedCompareExchange(pValue, 1, 0);
    }

    void *loadLibrary(const CHAR *pname) {
        return LoadLibraryA(pname);
    }

    void closeLibrary(void *phandle) {
        FreeLibrary((::HMODULE) phandle);
    }

    void *loadProcAddress(void *phandle, const CHAR *psym) {
        return (void*) GetProcAddress((::HMODULE) phandle, psym);
    }
}
