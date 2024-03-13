#include <Base/Mutex.h>

#if NW_OS(LINUX)

#include <Platform/Linux/LinuxBase.h>

namespace Neowise {
	void CMutex::lock() {
		while (_interlock == 1 || Platform::Linux::_InterlockValue(&_interlock) == 1) {}
	}

	void CMutex::unlock() {
		_interlock = 0;
	}

}

#endif
