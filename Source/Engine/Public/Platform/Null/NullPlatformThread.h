#pragma once

#include <Base/Thread.h>

namespace Neowise::Platform::Null {
    /**
    *
    */
    class NW_API CThread : public Neowise::CThread {
    public:
        CThread(PFN_StartFunc func, void* params, bool immediateDetach) 
        {}
        ~CThread() 
        {}

        bool isActive() const override { return false; }
        void detach() override		   {}
        void terminate() override	   {}
        void destroy() override		   {}
    };
}
