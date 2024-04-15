#pragma once

#include <Base/NumericTypes.h>
#include <Base/Allocators.h>
#include <Base/StringView.h>
#include <Base/UUID.h>

namespace Neowise {
    template<class> 
    class Ref;
    class CString;

    using CStringRef = Ref<CString>;

    /** 
    * A string class is used for stores and manipulates sequences of character objects.
    */
    class NW_API CString {
    public:
        CString();
        ~CString();
        CString(const char* str, TUint size);
        CString(const CStringView& sv);
        CString(const char* str);
        CString(const char c);

        CString(const CString&);
        CString(CString&&);
        CString& operator=(const CString&) = default;
        CString& operator=(CString&&) = default;

        TUint size() const;
        TUint capacity() const;
        bool empty() const;
        char* data() const;
        const char* cstr() const;
        TUint getCRC() const;
        void clear();

        const char* begin() const;
        const char* end() const;
        char* begin();
        char* end();

        bool operator==(const CString& r) const;
        bool operator!=(const CString& r) const;

        operator CStringView() const;

        char* find(const CStringView& sv) const;
        char* findReverse(const CStringView& sv) const;
        char* findFirst(const CStringView& set) const;
        char* findLast(const CStringView& set) const;
        bool  startsWith(const CStringView& str) const;
        bool  endsWith(const CStringView& str) const;

        CString& append(const CStringView& sv);
        CString& append(const char c, TUint count = 1);

        CString& operator+=(const CStringView& sv);
        CString& operator+=(const char c);

        CStringRef toRef() const;
    private:
        bool isSmall() const;
        bool fitSmall(TUint size) const;
        char* construct(const char* str, TUint size);

    private:
        struct NW_API _LargeData {
            constexpr _LargeData() = default;

            char*	strptr = nullptr;
            TUint	size = 0;
            TUint	capacity = 0;
        };

        struct NW_API _SmallData {
            constexpr _SmallData() = default;
            
            char	strbuf[sizeof(_LargeData) - sizeof(TUint8)] = {};
            TUint8	size = 0;
        };

        char*	ptr = nullptr;
        TUint	crc = {};
        union _StringRep {
            constexpr _StringRep() : large() 
            {}

            _LargeData large = {};
            _SmallData small;
        }
        rep = {};
    };

    template<>
    class NW_API CObjectHash<CString> {
    public:
        static TUint get(const CString& str) {
            return str.getCRC();
        }
    };

    class NW_API CStringBuilder : public NonCopyable, public NonMovable {
    public:
        CStringBuilder(CString& ref);
        ~CStringBuilder() = default;

        CStringBuilder& operator<<(const char* c_str);
        CStringBuilder& operator<<(const CStringView& sv);
        CStringBuilder& operator<<(const CString& str);
        CStringBuilder& operator<<(const TInt8 v);
        CStringBuilder& operator<<(const TUint8 v);
        CStringBuilder& operator<<(const TInt16 v);
        CStringBuilder& operator<<(const TUint16 v);
        CStringBuilder& operator<<(const TInt32 v);
        CStringBuilder& operator<<(const TUint32 v);
        CStringBuilder& operator<<(const TInt64 v);
        CStringBuilder& operator<<(const TUint64 v);
        CStringBuilder& operator<<(const TReal v);

    private:
        CString& data;
    };
}
