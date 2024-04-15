#pragma once

#include <Base/MacroUtils.h>
#include <Base/NumericTypes.h>

#include <initializer_list>

namespace Neowise {

    /**
     * std::initializer_list redefinition since EVERY c++ compiler
     * expexts this structure to be defined in order to use {this initializer}.
     */
    template<class T>
    using TInitializerList = std::initializer_list<T>;

    /**
     * struct RemoveRef used as template utility to get type T
     * without reference, if it exists.
     */
    template<class T>
    struct RemoveRef {
        using Type = T;
    };

    /**
     * struct RemoveRef used as template utility to get type T
     * without reference, if it exists.
     */
    template<class T>
    struct RemoveRef<T&> {
        using Type = T;
    };

    /**
     * struct RemoveRef used as template utility to get type T
     * without reference, if it exists.
     */
    template<class T>
    struct RemoveRef<T&&> {
        using Type = T;
    };

    /**
     * TRemoveRef used as template utility to get type T
     * without reference, if it exists.
     */
    template<class T>
    using TRemoveRef = typename RemoveRef<T>::Type;

    /**
     * Check if passed generic type is a pointer type.
     */
    template<class>
    constexpr bool isPointer = false;

    /**
     * Check if passed generic type is a pointer type.
     */
    template<class T>
    constexpr bool isPointer<T*> = true;

    /**
     * Check if passed generic type is l-value reference.
     */
    template<class>
    constexpr bool isLValReference = false;

    /**
     * Check if passed generic type is l-value reference.
     */
    template<class T>
    constexpr bool isLValReference<T&> = true;

    /**
     * Check if passed generic type is r-value reference.
     */
    template<class>
    constexpr bool isRValReference = false;

    /**
     * Check if passed generic type is r-value reference.
     */
    template<class T>
    constexpr bool isRValReference<T&&> = true;

    /**
     * Check if passed generic type is reference type.
     */
    template<class T>
    constexpr bool isReference = isLValReference<T> || isRValReference<T>;

    /**
     * Check if passed generic type comes with const-qualifier.
     */
    template<class>
    constexpr bool isConst = false;

    /**
     * Check if passed generic type comes with const-qualifier.
     */
    template<class T>
    constexpr bool isConst<const T> = true;

    /**
     * Utility structure to enable certain code constructions
     * if conditions are satisfied.
     */
    template<bool Cond, class T = void>
    struct EnableIf {};

    /**
     * Utility structure to enable certain code constructions
     * if conditions are satisfied.
     */
    template<class T>
    struct EnableIf<true, T> {
        using Type = T;
    };

    /**
     * Utility structure to enable certain code constructions
     * if conditions are satisfied.
     */
    template<bool Cond, class T>
    using TEnableIf = typename EnableIf<Cond, T>::Type;

    /**
     * Check is two passed generic types are the same.
     */
    template<class, class>
    constexpr bool isTypeOf = false;

    /**
     * Check is two passed generic types are the same.
     */
    template<class T>
    constexpr bool isTypeOf<T, T> = true;

    /**
     * Forward declaration of COptional<T>.
     */
    template<class>
    class COptional;

    /**
     * Check if passed generic type is COptonal<T> generic.
     */
    template<class>
    constexpr bool isOptional = false;

    /**
     * Check if passed generic type is COptonal<T> generic.
     */
    template<class T>
    constexpr bool isOptional<COptional<T>> = true;

    /**
     * Utility to get an integral type of certain floating point
     * type in order to access it's bits.
     */
    template<bool>
    struct FloatAsIntRep {
        using Type = void;
    };

    /**
     * Utility to get an integral type of certain floating point
     * type in order to access it's bits.
     */
    template<>
    struct FloatAsIntRep<true> {
        using Type = TUint32;
    };

    /**
     * Utility to get an integral type of certain floating point
     * type in order to access it's bits.
     */
    template<>
    struct FloatAsIntRep<false> {
        using Type = TUint64;
    };

    /**
     * Utility to get an integral type of certain floating point
     * type in order to access it's bits.
     */
    using TFloatAsIntRep = typename FloatAsIntRep<isTypeOf<TReal, TSingle>>::Type;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<class>
    static constexpr auto isIntegral = false;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TBool> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TBool> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TBool&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TBool&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TInt8> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TInt8> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TInt8&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TInt8&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TInt16> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TInt16> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TInt16&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TInt16&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TInt32> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TInt32> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TInt32&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TInt32&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TInt64> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TInt64> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TInt64&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TInt64&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TUint8> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TUint8> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TUint8&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TUint8&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TUint16> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TUint16> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TUint16&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TUint16&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TUint32> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TUint32> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TUint32&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TUint32&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TUint64> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TUint64> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<TUint64&> = true;

    /**
     * Check if passed generic type is integral (boolean, integer).
     */
    template<>
    static constexpr auto isIntegral<const TUint64&> = true;

    /**
     * Check if passed generic type is floating point.
     */
    template<class>
    static constexpr auto isFloatingPoint = false;

    /**
     * Check if passed generic type is floating point.
     */
    template<>
    static constexpr auto isFloatingPoint<TSingle> = true;

    /**
     * Check if passed generic type is floating point.
     */
    template<>
    static constexpr auto isFloatingPoint<const TSingle> = true;

    /**
     * Check if passed generic type is floating point.
     */
    template<>
    static constexpr auto isFloatingPoint<TSingle&> = true;

    /**
     * Check if passed generic type is floating point.
     */
    template<>
    static constexpr auto isFloatingPoint<const TSingle&> = true;

    /**
     * Check if passed generic type is numeric type.
     */
    template<class T>
    static constexpr auto isNumeric = isIntegral<T> || isFloatingPoint<T>;

    /**
     * Utility to get The Magic Value In Quake-III fast reversed square root.
     */
    template<bool>
    struct FloatPointEvilHack {
        static const auto value = TFloatAsIntRep();
    };

    /**
     * Utility to get The Magic Value In Quake-III fast reversed square root.
     */
    template<>
    struct FloatPointEvilHack<true> {
        static const auto value = TFloatAsIntRep(0x5f3759df);
    };

    /**
     * Utility to get The Magic Value In Quake-III fast reversed square root.
     */
    template<>
    struct FloatPointEvilHack<false> {
        static const auto value = TFloatAsIntRep(0x5fe6eb50c7b537a9);
    };

    /**
     * The Magic Value In Quake-III fast reversed square root.
     */
    constexpr auto kFpEvilHackValue = FloatPointEvilHack<isTypeOf<TReal, TSingle>>::value;
    
    /**
     * 
     */
    template<class T>
    constexpr auto alignmentOf = alignof(T);

    /**
     * 
     */
    template<TUint64 N>
    struct alignas(N) AlignBy {};

    /**
     * 
     */
    using nullptr_t = decltype(nullptr);

    /**
     * Compound data structure that holds data (T1, T2) tightly.
     */
    template<class T1, class T2>
    class CPair {
    public:
        ~CPair() = default;
        constexpr CPair() = default;
        constexpr CPair(const T1& t1, const T2& t2) 
            : first(t1), second(t2)
        {}

    public:
        T1 first;
        T2 second;
    };

    /**
     * Not allowed to perform copy on derived objects.
     */
    struct NW_API NonCopyable {
        NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };

    /**
     * Not allowed to perform move on derived objects.
     */
    struct NW_API NonMovable {
        NonMovable() = default;
        NonMovable(const NonMovable&) = delete;
        NonMovable& operator=(const NonMovable&) = delete;
    };
    
    /**
     * Not allowed to perform neither copy nor move on derived objects.
     */
    struct NW_API NonCopyableNonMovable : NonCopyable, NonMovable {};

    /**
     * Utility class to calculate hash of the generic object.
     */
    template<class T>
    class NW_API CObjectHash {
    public:
        static constexpr TUint get(const T& x) {
            return ((x << 5) + (x << 8));
        }
    };

    /**
     * Utility class to calculate hash of the TReal.
     */
    template<>
    class NW_API CObjectHash<TReal> {
    public: 
        static constexpr TUint get(const TReal& x) {
            return ((TUint(x) << 5) + TUint(x)) + 1ull;
        }
    };

    /**
     * Utility class to calculate hash of the TReal.
     */
    template<>
    class NW_API CObjectHash<const TReal> {
    public: 
        static constexpr TUint get(const TReal& x) {
            return ((TUint(x) << 5) + TUint(x)) + 1ull;
        }
    };

    /**
     * Utility class to calculate hash of the TReal.
     */
    template<>
    class NW_API CObjectHash<TReal&> {
    public: 
        static constexpr TUint get(const TReal& x) {
            return ((TUint(x) << 5) + TUint(x)) + 1ull;
        }
    };

    /**
     * Utility class to calculate hash of the TReal.
     */
    template<>
    class NW_API CObjectHash<const TReal&> {
    public: 
        static constexpr TUint get(const TReal& x) {
            return ((TUint(x) << 5) + TUint(x)) + 1ull;
        }
    };

}
