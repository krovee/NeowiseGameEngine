#pragma once

#include <Base/NumericTypes.h>
#include <Base/Scope.h>

namespace Neowise {
    /** 
    * OS wrapper around a mechanism to start and manage a new
    * thread within current process.
    */
    class NW_API CThread {
    public:
        using PFN_StartFunc = void(*)(void* params);

        virtual ~CThread() = default;

        virtual TBool isActive() const { return kFalse; }
        virtual void detach()		{}
        virtual void terminate()	{}
        virtual void destroy()		{}
        virtual void start()		{}

        static Scope<CThread> create(PFN_StartFunc func, void* params, TBool immediateStart = kFalse, TBool immediateDetach = kFalse);
    };
}
