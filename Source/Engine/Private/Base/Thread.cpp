#include <Base/Thread.h>

#include <Platform/PlatformThread.h>

namespace Neowise {
    Scope<CThread> CThread::create(PFN_StartFunc func, void* params, bool immediateStart, bool immediateDetach) {
        return makeScope<Platform::CThread>(func, params, immediateStart, immediateDetach).cast<CThread>();
    }
}
