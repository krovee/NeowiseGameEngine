#include <Base/StringUtils.h>
#include <Math/Math.h>

#include <Platform/PlatformMemory.h>

// TODO(krovee): Remove stdlib.h dependency
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>

namespace Neowise {

	bool CStringUtils::compare(const char* s1, const char* s2, uint64 len) {
		return Platform::CMemory::compare(s1, s2, len);
	}

	uint CStringUtils::length(const char* s) {
		return Platform::CMemory::counts(s);
	}

	uint CStringUtils::signedToString(char* s, int64 i) {
		return (uint)_snprintf_s(s, 24, 24, "%lli", i) + 1;
	}

	uint CStringUtils::unsignedToString(char* s, uint64 i) {
		return (uint)_snprintf_s(s, 24, 24, "%llu", i) + 1;
	}

	uint CStringUtils::realToString(char* s, real f) {
		return (uint) _snprintf_s(s, 16, 16, "%.4f", f);
	}

	char* CStringUtils::find(const char* cstr, uint64 csize, const char* substr, uint64 subsize) {
		for (uint64 i = 0; i < csize; ++i) {
			char* p = (char*)(cstr + i);
			if (compare(p, substr, subsize)) {
				return p;
			}
		}
		return nullptr;
	}

	char* CStringUtils::reverseFind(const char* cstr, uint64 csize, const char* substr, uint64 subsize) {
		for (int64 i = csize - subsize - 1; i >= 0; --i) {
			char* p = (char*)(cstr + i);
			if (compare(p, substr, subsize)) {
				return p;
			}
		}
		return nullptr;
	}

	char* CStringUtils::findFirst(const char* cstr, uint64 csize, const char* set, uint64 setlen) {
		for (uint64 i = 0; i < csize; ++i) {
			char* p = (char*)(cstr + i);
			for (uint64 k = 0; k < setlen; ++k) {
				if (*p == set[k]) {
					return p;
				}
			}
		}
		return nullptr;
	}

	char* CStringUtils::findFirst(const char* cstr, uint64 csize, const char* set) {
		return findFirst(cstr, csize, set, length(set));
	}

	char* CStringUtils::findLast(const char* cstr, uint64 csize, const char* set, uint64 setlen) {
		char* result = (char*)cstr;
		for (uint64 i = 0; i < csize; ++i) {
			char* p = (char*)(cstr + i);
			for (uint64 k = 0; k < setlen; ++k) {
				if (*p == set[k]) {
					result = p;
				}
			}
		}
		return result;
	}

	char* CStringUtils::findLast(const char* cstr, uint64 csize, const char* set) {
		return findLast(cstr, csize, set, length(set));
	}

}
