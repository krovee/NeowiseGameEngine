#include <Base/Thread.h>

#include <Platform/PlatformThread.h>

namespace Neowise {
    Scope<CThread> CThread::create(PFN_StartFunc func, void* params, TBool immediateStart, TBool immediateDetach) {
        return makeScope<Platform::CThread>(func, params, immediateStart, immediateDetach).cast<CThread>();
    }
}
