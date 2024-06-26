#pragma once

#include <Base/NumericTypes.h>
#include <Base/Templated.h>
#include <Base/UUID.h>

namespace Neowise {
    
    /** 
    * StringView class that wraps string immutably.
    */
    class NW_API CStringView {
    public:
        CStringView() = default;
        CStringView(const char* cstr);
        CStringView(const char* cstr, TUint64 size);
        CStringView(const char* cstr, TUint64 offset, TUint64 size);
        CStringView(const CStringView& sv, TUint64 offset);
        CStringView(const CStringView& sv) = default;
        CStringView(CStringView&& sv) = default;
        CStringView& operator=(const CStringView& sv) = default;
        CStringView& operator=(CStringView&& sv) = default;

        ~CStringView() = default;

        const char* cstr() const;
        TUint64 size() const;
        TBool empty() const;
        const CUUID getUUID() const; // WARN: Generated every call

        const char* begin() const;
        const char* end() const;

        char* find(const CStringView& sv) const;
        char* findReverse(const CStringView& sv) const;
        char* findFirst(const CStringView& set) const;
        char* findLast(const CStringView& set) const;
        TBool  startsWith(const CStringView& str) const;
        TBool  endsWith(const CStringView& str) const;

        TBool operator==(const CStringView& r) const;
        TBool operator!=(const CStringView& r) const;

        static TBool compareSizesLess(const CStringView& a, const CStringView& b);
        static TBool compareSizesGreater(const CStringView& a, const CStringView& b);
    private:
        const char*	_str = nullptr;
        TUint64		_size = 0;
        // CUUID		_uuid = {};
    };

}
