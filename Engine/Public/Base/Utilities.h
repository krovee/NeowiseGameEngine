#pragma once

#include <Base/NumericTypes.h>
#include <Base/Templated.h>
#include <new>

namespace Neowise {

	inline constexpr uint operator""_kb(long double kilobytes) {
		return uint(kilobytes * 1024.0);
	}

	inline constexpr uint operator""_mb(long double megabytes) {
		return uint(megabytes * 1024.0 * 1024.0);
	}

	inline constexpr long double operator""_gb(long double gigabytes) {
		return 1024.0 * 1024.0 * 1024.0 * gigabytes;
	}

	/**
	* Enumeration to determine build type in compile time, 
	* in a 'more c++ way'.
	*/
	enum EBuildType : uint {
		E_BUILD_TYPE_UNSPECIFIED,

		/**
		* Defined if build type is debug.
		*/
		E_BUILD_TYPE_DEBUG,

		/**
		* Defined if build type is release.
		*/
		E_BUILD_TYPE_RELEASE,

		/**
		* Defined if build type is shipped.
		*/
		E_BUILD_TYPE_SHIP,

		/**
		* Current build type.
		*/

#if		defined(_DEBUG)
		E_BUILD_TYPE = E_BUILD_TYPE_DEBUG
#elif	defined(NW_SHIP_BUILD)
		E_BUILD_TYPE = E_BUILD_TYPE_SHIP
#elif	defined(NDEBUG)
		E_BUILD_TYPE = E_BUILD_TYPE_RELEASE
#else 
		E_BUILD_TYPE = E_BUILD_TYPE_UNSPECIFIED
#endif
	};

	constexpr bool isDebugBuild		= E_BUILD_TYPE == E_BUILD_TYPE_DEBUG;
	constexpr bool isReleaseBuild	= E_BUILD_TYPE == E_BUILD_TYPE_RELEASE;
	constexpr bool isShipBuild		= E_BUILD_TYPE == E_BUILD_TYPE_SHIP;

	// [LINUX]: required line offset
	STATIC_ASSERT((isDebugBuild != isReleaseBuild) || (isReleaseBuild != isShipBuild));

	constexpr uint32 lrotate32bits(uint32 n, uint rot) {
		return (n << rot) | (n >> (32 - rot));
	}

	constexpr uint32 rrotate32bits(uint32 n, uint rot) {
		return (n >> rot) | (n << (32 - rot));
	}

	constexpr uint alignedSize(uint value, uint alignment) {
		return (value + alignment - 1) & ~(alignment - 1);
	}

	template<class T>
	constexpr T&& forward(TRemoveRef<T>&& t) {
		return static_cast<T&&>(t);
	}

	template<class T>
	constexpr T&& forward(TRemoveRef<T>& t) {
		return static_cast<T&&>(t);
	}

	template<class T>
	constexpr TRemoveRef<T>&& move(T&& t) {
		return static_cast<TRemoveRef<T>&&>(t);
	}

	template<class T>
	constexpr const void* addressof(const T& obj) {
		return reinterpret_cast<const void*>(&obj);
	}

	template<class T>
	constexpr void* addressof(T& obj) {
		return reinterpret_cast<void*>(&obj);
	}

	template<class T, class...Args>
	constexpr void construct_at(T& obj, Args&&...args) {
		new (addressof(obj)) T(forward<Args>(args)...);
	}

	template<class T, class U, class...Args>
	constexpr void construct_at(U* p, Args&&...args) {
		new (p) T(forward<Args>(args)...);
	}

	template<class T>
	constexpr void construct_at(T*& dst, T* src) {
		dst = src;
	}

	template<class T, class...Args>
	constexpr void construct_range(T* ptr, uint64 size, Args&&...args) {
		for (uint64 i = 0; i < size; ++i) {
			new ((ptr + i)) T(forward<Args>(args)...);
		}
	}

	template<class T>
	constexpr void destroy_at(T& obj) {
		obj.~T();
	}

	template<class T, class U = T>
	constexpr void destroy_at(U* ptr) {
		if (ptr) {
			ptr->~U();
		}
	}

	template<class T>
	constexpr auto destroy_range(T* ptr, uint64 size) {
		for (uint64 i = 0; i < size; ++i) {
			(ptr + i)->~T();
		}
	}

	template<class T>
	constexpr auto copy_range(T* dst, const T* src, uint64 size) {
		for (uint64 i = 0; i < size; ++i) {
			construct_at(dst[i], src[i]);
		}
	}

	template<class T>
	constexpr auto move_range(T* dst, T* src, uint64 size) {
		for (uint64 i = 0; i < size; ++i) {
			construct_at(dst[i], move(src[i]));
		}
	}

	template<class T>
	constexpr void swap(T& a, T& b) {
		T t(move(a));
		construct_at(a, move(b));
		construct_at(b, move(t));
	}

	template<class T, uint64 N>
	constexpr void swap(T(&l)[N], T(&r)[N]) {
		if (&l != &r) {
			T* f1 = l;
			T* l1 = f1 + N;
			T* f2 = r;
			for (; f1 != l1; ++f1, ++f2) {
				swap(*f1, *f2);
			}
		}
	}

	template<class T>
	constexpr void swap_range(T* dst, T* src, uint64 size) {
		for (uint64 i = 0; i < size; ++i) {
			swap(dst[i], src[i]);
		}
	}

	template<class T, uint N>
	constexpr uint arrayn(T(&)[N]) {
		return N;
	}

	constexpr uint32 toLittleEndian32(uint32 n) {
		if constexpr (NW_LITTLE_ENDIAN) {
			return((n << 24) & 0xFF000000)
				| ((n << 8)  & 0x00FF0000)
				| ((n >> 8)  & 0x0000FF00)
				| ((n >> 24) & 0x000000FF);
		}
		
		return n;
	}

	constexpr uint toLittleEndian64(uint n) {
		if constexpr (NW_LITTLE_ENDIAN) {
			return((n << 56) & 0xFF00000000000000)
				| ((n << 40) & 0x00FF000000000000)
				| ((n << 24) & 0x0000FF0000000000)
				| ((n << 8)  & 0x000000FF00000000)
				| ((n >> 8)  & 0x00000000FF000000)
				| ((n >> 24) & 0x0000000000FF0000)
				| ((n >> 40) & 0x000000000000FF00)
				| ((n >> 56) & 0x00000000000000FF);
		}

		return n;
	}

}
