#pragma once

#include <Base/Thread.h>

namespace Neowise::Platform::Null {
    /**
    *
    */
    class NW_API CThread : public Neowise::CThread {
    public:
        CThread(PFN_StartFunc func, void* params, TBool immediateDetach) 
        {}
        ~CThread() 
        {}

        TBool isActive() const override { return kFalse; }
        void detach() override		   {}
        void terminate() override	   {}
        void destroy() override		   {}
    };
}
