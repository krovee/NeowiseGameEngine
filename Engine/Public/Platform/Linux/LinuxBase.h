#pragma once

#include <Base/Common.h>
#include <Math/Math.h>
#include <Input/InputDevice.h>

namespace Neowise::Platform::Linux {

    enum EThreadError : uint {
        E_THREAD_ERROR_AGAIN,
        E_THREAD_ERROR_INVALID_VALUE,
        E_THREAD_ERROR_SEARCH,
        E_THREAD_ERROR_UNKNOWN
    };

    enum EWindowError : uint {
        E_WINDOW_ERROR_INVALID_ARGUMENTS,
        E_WINDOW_ERROR_X_MISSING,
        E_WINDOW_ERROR_BAD_FLUSH,
    };

    struct _WindowInputInfo {
        EToggleState    *pKeysState = nullptr;
        EKeyMod         *pKeyMods = nullptr;
    };

    using _WindowID = uint;

    void* _AlignedAlloc(uint size, uint alignment);
    void  _AlignedFree(void *p);
    void* _MemoryCopy(void *dst, const void *src, uint size);
    void* _MemorySet(void *dst, int32 value, uint size);
    uint  _MemoryCount(const char *s);
    uint  _MemoryCount(const wchar_t *ws);
    bool  _MemoryCompare(const void *p1, const void *p2, uint size);
    void  _ConsoleWrite(const char *text);
    real  _GetAbsoluteTime();
    uint  _ThreadCreate(uint& threadID, void *(*startFn)(void *), void *params);
    uint  _ThreadDetach(uint threadID);
    uint  _ThreadCancel(uint threadID);
    uint  _InterlockValue(volatile uint* pValue);
    void  _BreakProcess();
    uint  _WindowCreate(_WindowID& id, const CStringView& name, const Point2i& pos, const FVec2& size);
    uint  _WindowDestroy(_WindowID& id);
    bool  _WindowPumpMessages(const _WindowID& id, void* params);
    void  _WindowSetTitle(const _WindowID& id, const CStringView& name);
    void  _WindowSetPlacement(const _WindowID& id, const Point2i& pos, const FVec2& size);
    void  _TranslateKey(const uint in, EKey& key, EKeyMod& mod);    

}
