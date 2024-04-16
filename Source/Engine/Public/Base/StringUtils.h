#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
    /** 
    * Utility functions for work with strings.
    */
    class NW_API CStringUtils {
    public:
        static TBool compare(const char* s1, const char* s2, TUint64 len);
        static TUint length(const char* s);
        static TUint signedToString(char* s, TInt64 i);
        static TUint unsignedToString(char* s, TUint64 i);
        static TUint realToString(char* s, TReal f);
        static char* find(const char* cstr, TUint64 csize, const char* substr, TUint64 subsize);
        static char* reverseFind(const char* cstr, TUint64 csize, const char* substr, TUint64 subsize);
        static char* findFirst(const char* cstr, TUint64 csize, const char* set, TUint64 setlen);
        static char* findFirst(const char* cstr, TUint64 csize, const char* set);
        static char* findLast(const char* cstr, TUint64 csize, const char* set, TUint64 setlen);
        static char* findLast(const char* cstr, TUint64 csize, const char* set);
        static TUint  format(char *s, const char *fmt, ...);
        static TUint  format(char *s, TUint len, const char *fmt, ...);
        static TUint  format(char *s, const char *fmt, TVaList ap);
        static TUint  format(char *s, TUint len, const char *fmt, TVaList ap);

        static inline TBool endsWith(const char* s1, TUint64 len1, const char* s2, TUint64 len2) {
            if (len1 < len2) return kFalse;
            return compare(s1 + (len1 - len2), s2, len2);
        }
        
        static inline TBool startsWith(const char* s1, TUint64 len1, const char* s2, TUint64 len2) {
            if (len1 < len2) return kFalse;
            return compare(s1, s2, len2);
        }
    };
}
