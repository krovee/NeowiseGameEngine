#pragma once

#include <Base/Common.h>
#include <Math/Math.h>
#include <Input/InputDevice.h>

namespace Neowise::Platform::Linux {

    enum EThreadError : TUint {
        E_THREAD_ERROR_AGAIN,
        E_THREAD_ERROR_INVALID_VALUE,
        E_THREAD_ERROR_SEARCH,
        E_THREAD_ERROR_UNKNOWN
    };

    enum EWindowError : TUint {
        E_WINDOW_ERROR_INVALID_ARGUMENTS,
        E_WINDOW_ERROR_X_MISSING,
        E_WINDOW_ERROR_BAD_FLUSH,
    };

    struct _WindowInputInfo {
        EToggleState    *pKeysState = nullptr;
        EKeyMod         *pKeyMods = nullptr;
    };

    using _WindowID = TUint;

    void* _AlignedAlloc(TUint size, TUint alignment);
    void  _AlignedFree(void *p);
    void* _MemoryCopy(void *dst, const void *src, TUint size);
    void* _MemorySet(void *dst, TInt32 value, TUint size);
    TUint  _MemoryCount(const char *s);
    TUint  _MemoryCount(const wchar_t *ws);
    TBool  _MemoryCompare(const void *p1, const void *p2, TUint size);
    void  _ConsoleWrite(const char *text);
    TReal  _GetAbsoluteTime();
    TUint  _ThreadCreate(TUint& threadID, void *(*startFn)(void *), void *params);
    TUint  _ThreadDetach(TUint threadID);
    TUint  _ThreadCancel(TUint threadID);
    TUint  _InterlockValue(volatile TUint* pValue);
    void  _BreakProcess();
    TUint  _WindowCreate(_WindowID& id, const CStringView& name, const Point2i& pos, const FVec2& size);
    TUint  _WindowDestroy(_WindowID& id);
    TBool  _WindowPumpMessages(const _WindowID& id, void* params);
    void  _WindowSetTitle(const _WindowID& id, const CStringView& name);
    void  _WindowSetPlacement(const _WindowID& id, const Point2i& pos, const FVec2& size);
    void  _TranslateKey(const TUint in, EKey& key, EKeyMod& mod);   
    void* _LoadLibrary(const char* name);
    void  _FreeLibrary(void* handle);
    void* _GetProcAddress(void* handle, const char* sig); 

}
