#include <Base/StringUtils.h>
#include <Math/Math.h>

#include <Platform/PlatformMemory.h>

// TODO(krovee): Remove stdlib.h dependency
#include <stdarg.h>
#include <stdio.h>

namespace Neowise {

    bool CStringUtils::compare(const char* s1, const char* s2, TUint64 len) {
        return Platform::CMemory::compare(s1, s2, len);
    }

    TUint CStringUtils::length(const char* s) {
        return Platform::CMemory::counts(s);
    }

    TUint CStringUtils::signedToString(char* s, TInt64 i) {
        return format(s, 24, "%lli", i) + 1;
    }

    TUint CStringUtils::unsignedToString(char* s, TUint64 i) {
        return format(s, 24, "%llu", i) + 1;
    }

    TUint CStringUtils::realToString(char* s, TReal f) {
        return format(s, 16, "%.4f", f);
    }

    char* CStringUtils::find(const char* cstr, TUint64 csize, const char* substr, TUint64 subsize) {
        for (TUint64 i = 0; i < csize; ++i) {
            char* p = (char*)(cstr + i);
            if (compare(p, substr, subsize)) {
                return p;
            }
        }
        return nullptr;
    }

    char* CStringUtils::reverseFind(const char* cstr, TUint64 csize, const char* substr, TUint64 subsize) {
        for (TInt64 i = csize - subsize - 1; i >= 0; --i) {
            char* p = (char*)(cstr + i);
            if (compare(p, substr, subsize)) {
                return p;
            }
        }
        return nullptr;
    }

    char* CStringUtils::findFirst(const char* cstr, TUint64 csize, const char* set, TUint64 setlen) {
        for (TUint64 i = 0; i < csize; ++i) {
            char* p = (char*)(cstr + i);
            for (TUint64 k = 0; k < setlen; ++k) {
                if (*p == set[k]) {
                    return p;
                }
            }
        }
        return nullptr;
    }

    char* CStringUtils::findFirst(const char* cstr, TUint64 csize, const char* set) {
        return findFirst(cstr, csize, set, length(set));
    }

    char* CStringUtils::findLast(const char* cstr, TUint64 csize, const char* set, TUint64 setlen) {
        char* result = (char*)cstr;
        for (TUint64 i = 0; i < csize; ++i) {
            char* p = (char*)(cstr + i);
            for (TUint64 k = 0; k < setlen; ++k) {
                if (*p == set[k]) {
                    result = p;
                }
            }
        }
        return result;
    }

    char* CStringUtils::findLast(const char* cstr, TUint64 csize, const char* set) {
        return findLast(cstr, csize, set, length(set));
    }

    TUint CStringUtils::format(char *s, const char *fmt, ...) {
        va_list ap = {};
        va_start(ap, fmt);
#if NW_OS_TYPE_WIN32
        const auto maxlen = length(s);
        const TUint len = vsnprintf_s(s, maxlen, maxlen, fmt, ap);
#else
        const uint len = vsnprintf(s, length(s), fmt, ap);
#endif
        va_end(ap);
        return len;
    }

    TUint CStringUtils::format(char *s, TUint len, const char *fmt, ...) {
        va_list ap = {};
        va_start(ap, fmt);
#if NW_OS_TYPE_WIN32
        const TUint reallen = vsnprintf_s(s, len, len, fmt, ap);
#else
        const uint reallen = vsnprintf(s, len, fmt, ap);
#endif
        va_end(ap);
        return reallen;
    }

    TUint CStringUtils::format(char *s, const char *fmt, TVaList ap) {
#if NW_OS_TYPE_WIN32
        const auto maxlen = length(s);
        return vsnprintf_s(s, maxlen, maxlen, fmt, *(va_list*)ap);
#else
        return vsnprintf(s, length(s), fmt, *(va_list*)ap);
#endif
    }

    TUint CStringUtils::format(char *s, TUint len, const char *fmt, TVaList ap) {
#if NW_OS_TYPE_WIN32
        return vsnprintf_s(s, len, len, fmt, *(va_list*)ap);
#else
        return vsnprintf(s, len, fmt, *(va_list*)ap);
#endif
    }
}
