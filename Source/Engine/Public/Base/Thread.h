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

        virtual bool isActive() const { return false; }
        virtual void detach()		{}
        virtual void terminate()	{}
        virtual void destroy()		{}
        virtual void start()		{}

        static Scope<CThread> create(PFN_StartFunc func, void* params, bool immediateStart = false, bool immediateDetach = false);
    };
}
