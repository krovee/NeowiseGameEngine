#pragma once

#include <Base/NumericTypes.h>
#include <Base/Templated.h>

namespace Neowise {
    /**
     * 
     */
    template<class T, TUint N>
    class NW_API CStaticCycledBuffer {
    public:

        template<class...Args>
        void populate(TUint n, Args&&...args) {
            construct_range_cycled(n, forward<Args>(args)...);
        }
    private:
        TUint index(TUint offset = 0) const {
            return ((_size + offset) % kCapacity);
        }

        TUint rawIndex(TUint rawOffset = 0) const {
            return (((_size * sizeof(T)) + rawOffset) % kRawCapacity);
        }

        template<class...Args>
        void construct_range_cycled(TUint n, Args&&...args) {
            for (TUint i = 0; i < n; i++) {
                construct_at<T>(_buffer.typed + (i % kCapacity), forward<Args>(args)...);
                ++ _size;
            }
        }

        enum {
            kCapacity = N,
            kRawCapacity = N * sizeof(T)
        };

        union _Buffer {
            TUint8      raw[kRawCapacity] = {};
            T           typed[kCapacity];

            constexpr _Buffer() : raw() {}
            ~_Buffer() {
                destroy_range(typed, kCapacity);
            }
        }       _buffer = {};
        TUint   _size = {};
    };
}
