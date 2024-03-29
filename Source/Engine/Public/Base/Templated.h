#pragma once

#include <Base/MacroUtils.h>
#include <Base/NumericTypes.h>

#include <initializer_list>

namespace Neowise {
	template<class T>
	using TInitializerList = std::initializer_list<T>;

	template<class T>
	struct RemoveRef {
		using Type = T;
	};

	template<class T>
	struct RemoveRef<T&> {
		using Type = T;
	};

	template<class T>
	struct RemoveRef<T&&> {
		using Type = T;
	};

	template<class T>
	using TRemoveRef = typename RemoveRef<T>::Type;

	template<class>
	constexpr bool isPointer = false;

	template<class T>
	constexpr bool isPointer<T*> = true;

	template<class>
	constexpr bool isLValReference = false;

	template<class T>
	constexpr bool isLValReference<T&> = true;

	template<class>
	constexpr bool isRValReference = false;

	template<class T>
	constexpr bool isRValReference<T&&> = true;

	template<class T>
	constexpr bool isReference = isLValReference<T> || isRValReference<T>;

	template<class>
	constexpr bool isConst = false;

	template<class T>
	constexpr bool isConst<const T> = true;

	template<bool Cond, class T = void>
	struct EnableIf {};

	template<class T>
	struct EnableIf<true, T> {
		using Type = T;
	};

	template<bool Cond, class T>
	using TEnableIf = typename EnableIf<Cond, T>::Type;

	template<class, class>
	constexpr bool isTypeOf = false;

	template<class T>
	constexpr bool isTypeOf<T, T> = true;

	template<class>
	class COptional;

	template<class>
	constexpr bool isOptional = false;

	template<class T>
	constexpr bool isOptional<COptional<T>> = true;

	template<bool>
	struct FloatAsIntRep {
		using Type = void;
	};

	template<>
	struct FloatAsIntRep<true> {
		using Type = uint32;
	};

	template<>
	struct FloatAsIntRep<false> {
		using Type = uint64;
	};

	using TFloatAsIntRep = typename FloatAsIntRep<isTypeOf<real, single>>::Type;

	template<class>
	static constexpr auto isIntegral = false;

	template<>
	static constexpr auto isIntegral<bool> = true;

	template<>
	static constexpr auto isIntegral<const bool> = true;

	template<>
	static constexpr auto isIntegral<bool&> = true;

	template<>
	static constexpr auto isIntegral<const bool&> = true;

	template<>
	static constexpr auto isIntegral<int8> = true;

	template<>
	static constexpr auto isIntegral<const int8> = true;

	template<>
	static constexpr auto isIntegral<int8&> = true;

	template<>
	static constexpr auto isIntegral<const int8&> = true;

	template<>
	static constexpr auto isIntegral<int16> = true;

	template<>
	static constexpr auto isIntegral<const int16> = true;

	template<>
	static constexpr auto isIntegral<int16&> = true;

	template<>
	static constexpr auto isIntegral<const int16&> = true;

	template<>
	static constexpr auto isIntegral<int32> = true;

	template<>
	static constexpr auto isIntegral<const int32> = true;

	template<>
	static constexpr auto isIntegral<int32&> = true;

	template<>
	static constexpr auto isIntegral<const int32&> = true;

	template<>
	static constexpr auto isIntegral<int64> = true;

	template<>
	static constexpr auto isIntegral<const int64> = true;

	template<>
	static constexpr auto isIntegral<int64&> = true;

	template<>
	static constexpr auto isIntegral<const int64&> = true;

	template<>
	static constexpr auto isIntegral<uint8> = true;

	template<>
	static constexpr auto isIntegral<const uint8> = true;

	template<>
	static constexpr auto isIntegral<uint8&> = true;

	template<>
	static constexpr auto isIntegral<const uint8&> = true;

	template<>
	static constexpr auto isIntegral<uint16> = true;

	template<>
	static constexpr auto isIntegral<const uint16> = true;

	template<>
	static constexpr auto isIntegral<uint16&> = true;

	template<>
	static constexpr auto isIntegral<const uint16&> = true;

	template<>
	static constexpr auto isIntegral<uint32> = true;

	template<>
	static constexpr auto isIntegral<const uint32> = true;

	template<>
	static constexpr auto isIntegral<uint32&> = true;

	template<>
	static constexpr auto isIntegral<const uint32&> = true;

	template<>
	static constexpr auto isIntegral<uint64> = true;

	template<>
	static constexpr auto isIntegral<const uint64> = true;

	template<>
	static constexpr auto isIntegral<uint64&> = true;

	template<>
	static constexpr auto isIntegral<const uint64&> = true;

	template<class>
	static constexpr auto isFloatingPoint = false;

	template<>
	static constexpr auto isFloatingPoint<float> = true;

	template<>
	static constexpr auto isFloatingPoint<const float> = true;

	template<>
	static constexpr auto isFloatingPoint<float&> = true;

	template<>
	static constexpr auto isFloatingPoint<const float&> = true;

	template<class T>
	static constexpr auto isNumeric = isIntegral<T> || isFloatingPoint<T>;

	template<bool>
	struct FloatPointEvilHack {
		static const auto value = TFloatAsIntRep();
	};

	template<>
	struct FloatPointEvilHack<true> {
		static const auto value = TFloatAsIntRep(0x5f3759df);
	};

	template<>
	struct FloatPointEvilHack<false> {
		static const auto value = TFloatAsIntRep(0x5fe6eb50c7b537a9);
	};

	constexpr auto floatPointEvilHack = FloatPointEvilHack<isTypeOf<real, single>>::value;

	template<class T>
	constexpr auto alignmentOf = alignof(T);

	template<uint64 N>
	struct alignas(N) AlignBy {};

	using nullptr_t = decltype(nullptr);

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

	struct NW_API NonCopyable {
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

	struct NW_API NonMovable {
		NonMovable() = default;
		NonMovable(const NonMovable&) = delete;
		NonMovable& operator=(const NonMovable&) = delete;
	};
	
	struct NW_API NonCopyableNonMovable : NonCopyable, NonMovable {};

	template<class T>
	class NW_API CObjectHash {
	public:
		static constexpr uint get(const T& x) {
			return ((x << 5) + (x << 8));
		}
	};

	constexpr auto v = CObjectHash<uint>::get(251);

	template<>
	class NW_API CObjectHash<real> {
	public: 
		static constexpr uint get(const real& x) {
			return ((uint(x) << 5) + uint(x)) + 1ull;
		}
	};

	template<>
	class NW_API CObjectHash<const real> {
	public: 
		static constexpr uint get(const real& x) {
			return ((uint(x) << 5) + uint(x)) + 1ull;
		}
	};

	template<>
	class NW_API CObjectHash<real&> {
	public: 
		static constexpr uint get(const real& x) {
			return ((uint(x) << 5) + uint(x)) + 1ull;
		}
	};

	template<>
	class NW_API CObjectHash<const real&> {
	public: 
		static constexpr uint get(const real& x) {
			return ((uint(x) << 5) + uint(x)) + 1ull;
		}
	};

}