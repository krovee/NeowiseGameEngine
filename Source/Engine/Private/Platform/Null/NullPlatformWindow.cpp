#include <Platform/Null/NullPlatformWindow.h>

namespace Neowise::Platform::Null {

    CBaseWindow::CBaseWindow(defaultCreateTag)
    {
    }

    void CBaseWindow::update() {

    }

    TBool CBaseWindow::isOpen() const {
        return kFalse;
    }

    void CBaseWindow::setFullscreen(TBool) {

    }

    void CBaseWindow::setMaximized(TBool) {

    }

    void CBaseWindow::suspend(TBool) {

    }

    void* CBaseWindow::getNativeHandle() const {
        return nullptr;
    }

}
