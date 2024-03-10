#pragma once

#include "NumericTypes.h"

namespace Neowise {
	/** 
	* Common memory functions to operate over memory.
	*/
	struct NW_API Memory {
		/**
		* Copy bytes from 'src' to 'dst' for 'size'.
		*/
		static void* copy(void* dst, const void* src, uint64 size);
		
		/**
		* Fill 'dst' buffer with 'value' for 'size'.
		*/
		static void* fill(void* dst, const int32 value, uint64 size);
		
		/** 
		* Fill 'dst' buffer with zeros for 'size'.
		*/
		static void* clear(void* dst, uint64 size);
	};
}
