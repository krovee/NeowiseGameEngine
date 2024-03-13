#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
	/** 
	* Utility functions for work with strings.
	*/
	class NW_API CStringUtils {
	public:
		static bool compare(const char* s1, const char* s2, uint64 len);
		static uint length(const char* s);
		static uint signedToString(char* s, int64 i);
		static uint unsignedToString(char* s, uint64 i);
		static uint realToString(char* s, real f);
		static char* find(const char* cstr, uint64 csize, const char* substr, uint64 subsize);
		static char* reverseFind(const char* cstr, uint64 csize, const char* substr, uint64 subsize);
		static char* findFirst(const char* cstr, uint64 csize, const char* set, uint64 setlen);
		static char* findFirst(const char* cstr, uint64 csize, const char* set);
		static char* findLast(const char* cstr, uint64 csize, const char* set, uint64 setlen);
		static char* findLast(const char* cstr, uint64 csize, const char* set);
		static uint  format(char *s, const char *fmt, ...);
		static uint  format(char *s, uint len, const char *fmt, ...);
		static uint  format(char *s, const char *fmt, vaList ap);
		static uint  format(char *s, uint len, const char *fmt, vaList ap);

		static inline bool endsWith(const char* s1, uint64 len1, const char* s2, uint64 len2) {
			if (len1 < len2) return false;
			return compare(s1 + (len1 - len2), s2, len2);
		}
		
		static inline bool startsWith(const char* s1, uint64 len1, const char* s2, uint64 len2) {
			if (len1 < len2) return false;
			return compare(s1, s2, len2);
		}
	};
}
