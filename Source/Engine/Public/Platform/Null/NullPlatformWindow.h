#pragma once

#include <Engine/BaseWindow.h>

namespace Neowise::Platform::Null {
    /** 
    * 
    */
    class NW_API CBaseWindow : Neowise::CBaseWindow {
    public:
        struct defaultCreateTag {};

        CBaseWindow() = default;
        CBaseWindow(defaultCreateTag);
        virtual ~CBaseWindow() = default;

        void update() override;
        TBool isOpen() const override;
        void setFullscreen(TBool enable = kTrue) override;
        void setMaximized(TBool enable = kTrue) override;
        void suspend(TBool enable = kTrue) override;
        void* getNativeHandle() const override;
    };
}
