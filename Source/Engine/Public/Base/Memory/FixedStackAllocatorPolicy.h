#pragma once

#include <Base/Utilities.h>
#include <Base/Memory/AllocatorPolicyBase.h>

namespace Neowise {
    /** 
    * Fixed-size static stack-based allocator policy.
    */
    template<TUint64 N> 
    class NW_API CFixedStackAllocatorPolicy : public CAllocatorPolicyBase {
    public:

        constexpr CFixedStackAllocatorPolicy() {
            construct_range(_buffer, N, 0xdeadbeef);
        }

        virtual  ~CFixedStackAllocatorPolicy() = default;

        CFixedStackAllocatorPolicy(const CFixedStackAllocatorPolicy&) = default;
        constexpr CFixedStackAllocatorPolicy(CFixedStackAllocatorPolicy&& o) {
            swap(_buffer, o._buffer);
            swap(_allocated, o._allocated); 
            swap(_info, o._info);
        }
        CFixedStackAllocatorPolicy& operator=(const CFixedStackAllocatorPolicy&) = default;
        constexpr CFixedStackAllocatorPolicy& operator=(CFixedStackAllocatorPolicy&& r) {
            swap(_buffer, r._buffer);
            swap(_allocated, r._allocated);
            swap(_info, r._info);
            return *this;
        }

        constexpr void destroy() override {}

        inline void* allocate(TUint64 size) override {
            if (_allocated < N && size) {
                const TUint64 i = _allocated;
                _allocated += size;
                onAllocate(size);
                return reinterpret_cast<void*>(&_buffer[i]);
            }
            return nullptr;
        }

        inline void* getBuffer() {
            return _buffer;
        }

        inline void free(void* p, TUint64 size) override {
            if (size <= _allocated) {
                _allocated -= size;
                onFree(size);
                if (TInt64(_allocated) < 0) {
                    _allocated = 0;
                }
                if (p) {
                    Memory::clear(p, size);
                }
            }
        }

    private:
        alignas(8)
        TUint8	_buffer[N] = {};
        TUint64	_allocated = {};

        template<TUint64 M>
        friend constexpr void swap(CFixedStackAllocatorPolicy<M>& a, CFixedStackAllocatorPolicy<M>& b);
    };

    template<TUint64 N>
    constexpr void swap(CFixedStackAllocatorPolicy<N>& a, CFixedStackAllocatorPolicy<N>& b) {
        swap(a._buffer, b._buffer);
        swap(a._allocated, b._allocated);
        swap(a._info, b._info);
    }

}
