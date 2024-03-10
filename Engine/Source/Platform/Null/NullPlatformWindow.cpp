#include <Platform\Null\NullPlatformWindow.h>

namespace Neowise::Platform {

	Null::CBaseWindow::CBaseWindow(defaultCreateTag)
	{
	}

	void Null::CBaseWindow::update() {

	}

	bool Null::CBaseWindow::isOpen() const {
		return false;
	}

	void Null::CBaseWindow::setFullscreen(bool) {

	}

	void Null::CBaseWindow::setMaximized(bool) {

	}

	void Null::CBaseWindow::suspend(bool) {

	}

	void* Null::CBaseWindow::getNativeHandle() const {
		return nullptr;
	}

}
