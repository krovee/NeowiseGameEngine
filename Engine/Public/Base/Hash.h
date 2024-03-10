#pragma once

#include <Base/NumericTypes.h>
#include <Base/StringView.h>

namespace Neowise {
	enum : uint64 {
		FNV64_PRIME		= 0x100000001b3ULL,
		FNV64_INITIAL	= 0xcbf29ce484222325ULL
	};

	/** 
	* Hashing algorithm utility class, based on FNV64-1a algorithm.
	*/
	class NW_API CHash {
	public:
		CHash(uint64 offset = FNV64_INITIAL);

		void offset(uint64 value);

		uint64 operator()(const CStringView& sv);
		uint64 operator()(const char* str, uint64 size);
		uint64 operator()(const void* arr, uint64 elemSize, uint64 count);
	private:
		uint64 _offset = {};
	};
}
