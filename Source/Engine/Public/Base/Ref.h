#pragma once

#include <Base/Assert.h>
#include <Base/Allocators.h>

namespace Neowise {
    extern CFixedHeapAllocatorPolicy* GAlloc;

    template<class T>
    class Ref {
    public:
        enum class EInPlaceCtorTag { val };
        enum class ECastCtorTag { val };

        constexpr Ref() = default;
        constexpr Ref(std::nullptr_t) : ptr() {}
        
        ~Ref() {
            destroy();
        }

        template<class...Args>
        constexpr Ref(EInPlaceCtorTag, Args&&...args) {
            construct(forward<Args>(args)...);
        }

        template<class U>
        constexpr Ref(ECastCtorTag, U&& uobj) {
            construct(move(uobj));
        }

        constexpr Ref(const Ref& o) : ptr(o.ptr) {
            ++ptr->refCount;
        }

        constexpr Ref(Ref&& o) : ptr(o.ptr) {
            ++ptr->refCount;
        }

        constexpr Ref& operator=(const Ref& o) {
            ptr = o.ptr;
            ++ptr->refCount;
            return *this;
        }

        constexpr Ref& operator=(Ref&& o) {
            ptr = o.ptr;
            ++ptr->refCount;
            return *this;
        }

        template<class U>
        Ref<U> cast() {
            auto p = release();
            return Ref<U>(ECastCtorTag::val, move(*p));
        }

        const T* get() const {
            return reinterpret_cast<const T*>(addressof(ptr->obj));
        }

        T* get() {
            return reinterpret_cast<T*>(addressof(ptr->obj));
        }

        operator TBool() const {
            return ptr;
        }

        T& operator*() {
            return ptr->obj;
        }

        const T& operator*() const {
            return ptr->obj;
        }

        T* operator->() {
            return get();
        }

        const T* operator->() const {
            return get();
        }

        T* release() {
            NW_ASSERT(ptr, "Failed to release an empty ref!");

            auto p = get();
            ptr = nullptr;
            return p;
        }

        void reset(T* p = {}) {
            NW_ASSERT(p, "Failed to reset to an empty pointer!");

            if (ptr) {
                destroy_at(ptr->obj);

                if (p) {
                    auto& objref = *p;
                    swap(ptr->obj, objref);
                }
            }
        }

        void reset(nullptr_t) {
            auto p = get();
            ptr = nullptr;
        }

    private:
        template<class...Args>
        constexpr void construct(Args&&...args) {
            destroy();

            ptr = reinterpret_cast<RefData*>(GAlloc->allocate(sizeof(RefData)));
            ptr->refCount = 1;
            construct_at(ptr->obj, forward<Args>(args)...);
        }

        constexpr void destroy() {
            if (ptr) {
                --ptr->refCount;

                if (ptr->refCount == 0) {
                    destroy_at(ptr->obj);
                }
            }
        }

    private:
        struct RefData {
            T obj;
            int refCount;
        };

        RefData* ptr = nullptr;
    };

    template<class T, class...Args>
    constexpr Ref<T> makeRef(Args&&...args) {
        return Ref<T>(Ref<T>::EInPlaceCtorTag::val, forward<Args>(args)...);
    }
}
