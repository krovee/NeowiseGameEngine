#pragma once

#include "WindowsBase.h"
#include <Base/Thread.h>

namespace Neowise::Platform::Windows {
    /** 
    * 
    */
    class NW_API CThread : public Neowise::CThread {
    public:
        CThread(PFN_StartFunc func, void* params, bool immediateStart, bool immediateDetach);
        ~CThread();

        void start() override;
        bool isActive() const override;
        void detach() override;
        void terminate() override;
        void destroy() override;

    private:
        HANDLE _hHandle = nullptr;
        DWORD  _id = 0;
    };
}
