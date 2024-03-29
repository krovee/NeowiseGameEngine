#include <Engine/BaseWindow.h>

#include <Platform/PlatformWindow.h>

namespace Neowise {
	
	Point2i CBaseWindow::getPosition() const {
		return _pos;
	}
	
	int32 CBaseWindow::getX() const {
		return _pos.x;
	}
	
	int32 CBaseWindow::getY() const {
		return _pos.y;
	}
	
	FVec2 CBaseWindow::getSize() const {
		return _size;
	}
	
	real CBaseWindow::getWidth() const {
		return _size.x;
	}
	
	real CBaseWindow::getHeight() const {
		return _size.y;
	}
	
	bool CBaseWindow::isFullscreen() const {
		return _flags.isFullscreen;
	}
	
	bool CBaseWindow::isMaximized() const {
		return _flags.isMaximized;
	}
	
	bool CBaseWindow::isSuspended() const {
		return _flags.isSuspended;
	}
	
	bool CBaseWindow::isFocused() const {
		return _flags.isFocused;
	}


	Scope<CBaseWindow> CBaseWindow::createDefault(bool maximized, bool fullscreen) {
		auto w = makeScope<Platform::CBaseWindow>(Platform::CBaseWindow::defaultCreateTag{});
		w->setFullscreen(fullscreen);
		w->setMaximized(maximized);
		return move(w.cast<CBaseWindow>());
	}

	CBaseWindow::CBaseWindow(const Point2i& pos, const FVec2& size, bool isfull, bool ismax, bool issusp, bool isfoc)
		: _pos(pos), _size(size), _flags{ isfull, ismax, issusp, isfoc }
	{
	}
}
