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
        bool isOpen() const override;
        void setFullscreen(bool enable = true) override;
        void setMaximized(bool enable = true) override;
        void suspend(bool enable = true) override;
        void* getNativeHandle() const override;
    };
}
