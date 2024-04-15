#pragma once

#include <Base/NumericTypes.h>
#include <Base/Scope.h>

namespace Neowise {
    /** 
    * Simplest synchronization primitive.
    */
    class NW_API CMutex : public NonCopyable {
    public:
        constexpr CMutex() = default;
        ~CMutex() {}

    private:
        void lock();
        void unlock();

    private:
        friend class CScopedLock;
    private:
        volatile TUint _interlock = 0;
    };

    /** 
    * An utility to lock passed mutex at this wrapper creation time,
    * and to unlock it at destruction.
    */
    class NW_API CScopedLock {
    public:
        inline CScopedLock(CMutex& mtx)
            : _mtx(mtx)
        {
            _mtx.lock();
        }

        inline ~CScopedLock() {
            _mtx.unlock();
        }

    private:
        CMutex& _mtx;
    };
}
