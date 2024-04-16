#include <Platform/Windows/WindowsPlatformThread.h>

namespace Neowise::Platform::Windows {
    CThread::CThread(PFN_StartFunc func, void* params, TBool immediateStart, TBool immediateDetach) {
        _hHandle = createThread(func, params, &_id);
        if (immediateStart) {
            resumeThread(_hHandle);
        }
        if (immediateDetach) {
            closeHandle(_hHandle);
        }
    }

    CThread::~CThread() {
        if (isActive()) {
            destroy();
        }
    }

    void CThread::start() {
        if (_hHandle) {
            resumeThread(_hHandle);
        }
    }

    TBool CThread::isActive() const {
        if (_hHandle) {
            DWORD exCode = waitForSingleObject(_hHandle, 0);
            if (exCode == E_WAIT_TIMEOUT) {
                return kTrue;
            }
        }
        return kFalse;
    }

    void CThread::detach() {
        if (_hHandle) {
            closeHandle(_hHandle);
            _hHandle = nullptr;
        }
    }

    void CThread::terminate() {
        if (_hHandle) {
            terminateThread(_hHandle, 0);
            _hHandle = nullptr;
        }
    }

    void CThread::destroy() {
        if (_hHandle) {
            DWORD exCode = 0;
            getExitCodeThread(_hHandle, &exCode);
            if (exCode == 259) // thread is still running 
            {
                terminateThread(_hHandle, 0);
            }
            closeHandle(_hHandle);
            _hHandle = nullptr;
            _id = 0;
        }
    }

}
