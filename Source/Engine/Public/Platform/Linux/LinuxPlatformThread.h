#pragma once

#include <Base/Thread.h>

namespace Neowise::Platform::Linux {
    /**
    *
    */
    class NW_API CThread : public Neowise::CThread {
    public:
        CThread(PFN_StartFunc func, void* params, TBool immediateStart, TBool immediateDetach);
        ~CThread();

        // Probably useless method on linux...
        void start() override;
        TBool isActive() const override; 
        void detach() override; 
        void terminate() override; 
        void destroy() override; 

    private:
        TUint id = {};
        TUint* sharedID = nullptr;
    };
}
