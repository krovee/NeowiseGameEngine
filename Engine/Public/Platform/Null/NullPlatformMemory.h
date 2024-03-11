#pragma once

#include <Base/NumericTypes.h>

namespace Neowise::Platform::Null {
	/** 
	* 
	*/
	class NW_API CMemory {
	public:
		static void* allocate(uint64 size);
		static void  free(void* p);
		static void* copy(void* dst, void* src, uint64 size);
		static void* fill(void* dst, int32 value, uint64 size);
		static uint64 counts(const char* s);
		static uint64 counts(const wchar_t* ws);
	};
}
