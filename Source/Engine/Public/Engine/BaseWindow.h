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
            bool isFullscreen = false;
            bool isMaximized = false;
            bool isSuspended = false;
            bool isFocused = false;
        };

        CBaseWindow() = default;
        virtual ~CBaseWindow() = default;

        virtual void update() {}
        virtual bool isOpen() const { return false; }
        virtual void setFullscreen(bool enable = true) { NW_UNUSED(enable); }
        virtual void setMaximized(bool enable = true) { NW_UNUSED(enable); }
        virtual void setTitle(const CString& title) { NW_UNUSED(title); }
        virtual void suspend(bool enable = true) { NW_UNUSED(enable); }
        virtual void* getNativeHandle() const { return nullptr; }

        Point2i getPosition() const;
        TInt32 getX() const;
        TInt32 getY() const;
        FVec2 getSize() const;
        TReal getWidth() const;
        TReal getHeight() const;
        bool isFullscreen() const;
        bool isMaximized() const;
        bool isSuspended() const;
        bool isFocused() const;

        static Scope<CBaseWindow> createDefault(bool maximized = false, bool fullscreen = false);
    protected:
        CBaseWindow(const Point2i& pos, const FVec2& size, bool isfull, bool ismax, bool issusp, bool isfoc);

    protected:
        Point2i	_pos = {};
        FVec2	_size = {};
        Flags	_flags = {};
    };
}
