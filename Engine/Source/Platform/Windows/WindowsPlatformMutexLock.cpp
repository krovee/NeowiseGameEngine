#include <Platform/Windows/WindowsBase.h>

#if NW_OS(WIN32)

#include <Base/Mutex.h>

namespace Neowise {
	void CMutex::lock() {
		while (_interlock == 1 || Platform::Windows::interlockValue(&_interlock) == 1) {}
	}

	void CMutex::unlock() {
		_interlock = 0;
	}

}

#endif
