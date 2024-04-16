#pragma once

#include <Base/NumericTypes.h>
#include <Base/Utilities.h>

namespace Neowise {
    struct TNullopt {};
    static constexpr TNullopt nullopt;

    /** 
    * Simple container that manages optional contained value.
    */
    template<class T>
    class NW_API TOptional {
    public:
        constexpr TOptional() = default;

        constexpr ~TOptional() {
            destruct();
            check = kFalse;
        }

        constexpr TOptional(TNullopt) {}
        
        constexpr TOptional(const TOptional& o) {
            if (o.hasValue()) {
                construct(o.unwrap());
            }
        }
        
        constexpr TOptional(TOptional&& o) {
            if (o.hasValue()) {
                construct(move(o.unwrap()));
            }
        }
        
        template<class U>
        constexpr TOptional(const TOptional<U>& o) {
            if (o.hasValue()) {
                construct(o.unwrap());
            }
        }
        
        template<class U>
        constexpr TOptional(TOptional<U>&& o) {
            if (o.hasValue()) {
                construct(move(o.unwrap()));
            }
        }

        template<class...Args>
        constexpr TOptional(Args&&...args) {
            construct(forward<Args>(args)...);
        }

        constexpr TOptional& operator=(TNullopt) {
            reset();
            return *this;
        }

        constexpr TOptional& operator=(const TOptional& r) {
            if (r.hasValue()) {
                if (hasValue()) {
                    unwrap() = r.unwrap();
                }
                else {
                    construct(r.unwrap());
                }
            }
            else {
                reset();
            }

            return *this;
        }

        template<class U>
        constexpr TOptional& operator=(const TOptional<U>& r) {
            if (r.hasValue()) {
                if (hasValue()) {
                    unwrap() = r.unwrap();
                }
                else {
                    construct(r.unwrap());
                }
            }
            else {
                reset();
            }

            return *this;
        }

        constexpr TOptional& operator=(TOptional&& r) {
            if (r.hasValue()) {
                if (hasValue()) {
                    unwrap() = move(r.unwrap());
                }
                else {
                    construct(move(r.unwrap()));
                }
            }
            else {
                reset();
            }

            return *this;
        }

        template<class U>
        constexpr TOptional& operator=(TOptional<U>&& r) {
            if (r.hasValue()) {
                if (hasValue()) {
                    unwrap() = move(r.unwrap());
                }
                else {
                    construct(move(r.unwrap()));
                }
            }
            else {
                reset();
            }

            return *this;
        }

        template<class...Args>
        constexpr T& emplace(Args&&...args) {
            reset();
            construct(forward<Args>(args)...);
            return unwrap();
        }

        constexpr TBool hasValue() const {
            return check;
        }

        constexpr operator TBool() const {
            return check;
        }

        constexpr T& unwrap() {
            return static_cast<T&>(*(T*)(getStorage()));
        }

        constexpr const T& unwrap() const {
            return static_cast<const T&>(*(const T*)(getStorage()));
        }

        constexpr T* ptr() {
            return static_cast<T*>(getStorage());
        }

        constexpr const T* ptr() const {
            return static_cast<const T*>(getStorage());
        }

        constexpr T* operator->() {
            return &unwrap();
        }
        
        constexpr const T* operator->() const {
            return &unwrap();
        }
        
        constexpr T& operator*() {
            return unwrap();
        }
        
        constexpr const T& operator*() const {
            return unwrap();
        }

        constexpr void reset() {
            if (hasValue()) {
                destruct();
                check = kFalse;
            }
        }

        constexpr void swap(TOptional& r) {
            if (r.hasValue()) {
                if (hasValue()) {
                    Neowise::swap(unwrap(), r.unwrap());
                }
                else {
                    construct(move(r.unwrap()));
                    r.reset();
                }
            }
            else {
                if (hasValue()) {
                    r.construct(move(unwrap()));
                    reset();
                }
            }
        }

        template<class U>
        constexpr TBool operator==(const TOptional<U>& r) const {
            if (hasValue() != hasValue()) return kFalse;
            if (!hasValue()) return kTrue;
            return unwrap() == r.unwrap();
        }

        template<class U>
        constexpr TBool operator!=(const TOptional<U>& r) const {
            return !(*this == r);
        }
    private:
        STATIC_ASSERT(!isOptional<T>);
        STATIC_ASSERT(!isConst<T>);
        STATIC_ASSERT(!isLValReference<T>);
        STATIC_ASSERT(!isRValReference<T>);
    private:
        constexpr void* getStorage() {
            return reinterpret_cast<void*>(storage);
        }

        constexpr const void* getStorage() const {
            return reinterpret_cast<const void*>(storage);
        }

        template<class...Args>
        constexpr void construct(Args&&...args) {
            NW_ASSERT(!hasValue(), "Failed to construct optional that already have a value!");
            construct_at<T>(getStorage(), forward<Args>(args)...);
            check = kTrue;
        }

        constexpr void destruct() {
            if (hasValue()) {
                destroy_at(unwrap());
            }
        }

    private:
        TUint8	storage[alignedSize(sizeof(T), alignmentOf<T>)] = {};
        TBool	check = kFalse;
    };
}
