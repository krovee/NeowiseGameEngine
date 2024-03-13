#include <Platform/Linux/LinuxPlatformThread.h>

#if NW_OS(LINUX)

#include <Platform/Linux/LinuxBase.h>
#include <Base/Diagnostics.h>
#include <Engine/EngineLoop.h>

namespace Neowise::Platform::Linux {
    CThread::CThread(PFN_StartFunc func, void* params, bool immediateStart, bool immediateDetach) {
        NW_ASSERT(func, "Failed to create a thread without work!");

        {
            const auto ret = _ThreadCreate(id, (void *(*)(void *))func, params);
            if (ret) {
                switch (ret) {
                    case E_THREAD_ERROR_INVALID_VALUE: {
                        GDiag << "Failed to create thread: invalid settings were passed in attributes..\n";
                        GEngineLoop->requestExit(124);
                    } return;
                    case E_THREAD_ERROR_AGAIN: {
                        GDiag << "Failed to create thread: insufficient resources to create another thread.\n";
                        GEngineLoop->requestExit(129);
                    } return;
                                        
                    default:
                    case E_THREAD_ERROR_UNKNOWN: {
                        GDiag << "Failed to create thread: an unhandled error has occurred. (" << ret << ")\n";
                        GEngineLoop->requestExit(131);
                    } return;
                }
            }
        }

        GDiag << "Starting thread.. (ID=" << id << ")\n";

        if (!immediateDetach) {
            sharedID = (uint*)GAlloc->allocate(sizeof id);
            *sharedID = id;
        }
        else {
            const auto ret = _ThreadDetach(id);
            if (ret) {
                switch (ret) {
                    case E_THREAD_ERROR_INVALID_VALUE: {
                        GDiag << "Failed to detach newly-created thread: thread is not a joinable thread.\n";
                        GEngineLoop->requestExit(124);
                    } return;
                    case E_THREAD_ERROR_SEARCH: {
                        GDiag << "Failed to detach newly-created thread: no thread with the id " << id << " could be found.\n";
                        GEngineLoop->requestExit(134);
                    } return;
                                        
                    default:
                    case E_THREAD_ERROR_UNKNOWN: {
                        GDiag << "Failed to detach newly-created thread: an unknown error has occurred. (" << ret << ")\n";
                        GEngineLoop->requestExit(131);
                    } return;
                }
            }
        }
    }

    CThread::~CThread() {
        if (isActive()) {
            destroy();
        }
    }

    void CThread::start() {
        NW_OPT_ASSERT(false, "[LINUXNOTIMPLEMENTED]: Failed to start() linux thread, because newly created threads start immediately!");
    }

    bool CThread::isActive() const {
        return sharedID != nullptr;
    }

    void CThread::detach() {
        if (sharedID) {
            const auto ret = _ThreadDetach(*sharedID);
            if (ret) {
                switch (ret) {
                    case E_THREAD_ERROR_SEARCH: {
                        GDiag << "Failed to detach thread: no thread with the id " << id << " could be found.\n";
                        GEngineLoop->requestExit(144);
                    } return;
                    case E_THREAD_ERROR_INVALID_VALUE: {
                        GDiag << "Failed to detach thread: thread is not a joinable thread.\n";
                        GEngineLoop->requestExit(145);
                    } return;
                    
                    default:
                    case E_THREAD_ERROR_UNKNOWN: {
                        GDiag << "Failed to detach thread: an unknown error has occurred. (" << ret << ")\n";
                        GEngineLoop->requestExit(141);
                    } return;
                }
            }
            GAlloc->free(sharedID, sizeof id);
            sharedID = nullptr;
        }
    }

    void CThread::terminate() {
        destroy();
    }

    void CThread::destroy() {
        if (sharedID) {
            const auto ret = _ThreadCancel(*sharedID);
            if (ret) {
                switch (ret) {
                    case E_THREAD_ERROR_SEARCH: {
                        GDiag << "Failed to cancel thread: no thread with the id " << id << " could be found.\n";
                        GEngineLoop->requestExit(144);
                    } return;
                    
                    default:
                    case E_THREAD_ERROR_UNKNOWN: {
                        GDiag << "Failed to cancel thread: an unknown error has occurred. (" << ret << ")\n";
                        GEngineLoop->requestExit(141);
                    } return;
                }
            }
            GAlloc->free(sharedID, sizeof id);
            sharedID = nullptr;
            id = 0;
        }
    }

}

#endif
