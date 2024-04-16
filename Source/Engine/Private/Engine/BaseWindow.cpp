#include <Engine/BaseWindow.h>

#include <Platform/PlatformWindow.h>

namespace Neowise {
    
    Point2i CBaseWindow::getPosition() const {
        return _pos;
    }
    
    TInt32 CBaseWindow::getX() const {
        return _pos.x;
    }
    
    TInt32 CBaseWindow::getY() const {
        return _pos.y;
    }
    
    FVec2 CBaseWindow::getSize() const {
        return _size;
    }
    
    TReal CBaseWindow::getWidth() const {
        return _size.x;
    }
    
    TReal CBaseWindow::getHeight() const {
        return _size.y;
    }
    
    TBool CBaseWindow::isFullscreen() const {
        return _flags.isFullscreen;
    }
    
    TBool CBaseWindow::isMaximized() const {
        return _flags.isMaximized;
    }
    
    TBool CBaseWindow::isSuspended() const {
        return _flags.isSuspended;
    }
    
    TBool CBaseWindow::isFocused() const {
        return _flags.isFocused;
    }


    Scope<CBaseWindow> CBaseWindow::createDefault(TBool maximized, TBool fullscreen) {
        auto w = makeScope<Platform::CBaseWindow>(Platform::CBaseWindow::defaultCreateTag{});
        w->setFullscreen(fullscreen);
        w->setMaximized(maximized);
        return move(w.cast<CBaseWindow>());
    }

    CBaseWindow::CBaseWindow(const Point2i& pos, const FVec2& size, TBool isfull, TBool ismax, TBool issusp, TBool isfoc)
        : _pos(pos), _size(size), _flags{ isfull, ismax, issusp, isfoc }
    {
    }
}
