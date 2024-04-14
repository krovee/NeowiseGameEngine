#include <Platform/Null/NullPlatformWindow.h>

namespace Neowise::Platform::Null {

    CBaseWindow::CBaseWindow(defaultCreateTag)
    {
    }

    void CBaseWindow::update() {

    }

    bool CBaseWindow::isOpen() const {
        return false;
    }

    void CBaseWindow::setFullscreen(bool) {

    }

    void CBaseWindow::setMaximized(bool) {

    }

    void CBaseWindow::suspend(bool) {

    }

    void* CBaseWindow::getNativeHandle() const {
        return nullptr;
    }

}
