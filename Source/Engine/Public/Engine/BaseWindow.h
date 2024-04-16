#pragma once

#include <Base/Common.h>
#include <Math/Point.h>

namespace Neowise {
    /** 
    * System basic window with no extra context.
    */
    class NW_API CBaseWindow {
    public:
        struct Flags {
            TBool isFullscreen = kFalse;
            TBool isMaximized = kFalse;
            TBool isSuspended = kFalse;
            TBool isFocused = kFalse;
        };

        CBaseWindow() = default;
        virtual ~CBaseWindow() = default;

        virtual void update() {}
        virtual TBool isOpen() const { return kFalse; }
        virtual void setFullscreen(TBool enable = kTrue) { NW_UNUSED(enable); }
        virtual void setMaximized(TBool enable = kTrue) { NW_UNUSED(enable); }
        virtual void setTitle(const CString& title) { NW_UNUSED(title); }
        virtual void suspend(TBool enable = kTrue) { NW_UNUSED(enable); }
        virtual void* getNativeHandle() const { return nullptr; }

        Point2i getPosition() const;
        TInt32 getX() const;
        TInt32 getY() const;
        FVec2 getSize() const;
        TReal getWidth() const;
        TReal getHeight() const;
        TBool isFullscreen() const;
        TBool isMaximized() const;
        TBool isSuspended() const;
        TBool isFocused() const;

        static Scope<CBaseWindow> createDefault(TBool maximized = kFalse, TBool fullscreen = kFalse);
    protected:
        CBaseWindow(const Point2i& pos, const FVec2& size, TBool isfull, TBool ismax, TBool issusp, TBool isfoc);

    protected:
        Point2i	_pos = {};
        FVec2	_size = {};
        Flags	_flags = {};
    };
}
