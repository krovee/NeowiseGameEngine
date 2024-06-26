#include <Base/Common.h>
#include <Base/StringUtils.h>
#include <Engine/EngineGlobals.h>
#include <Base/CRC.h>

namespace Neowise {
    CString::CString() {
        ptr = rep.small.strbuf;
    }

    CString::~CString() {
        if (!isSmall() && ptr) {
            GAlloc->free(ptr, size());
        }
    }

    CString::CString(const char* str, TUint size) {
        ptr = construct(str, size);
        crc = CRC64(str, size);
    }

    CString::CString(const CStringView& sv) {
        ptr = construct(sv.cstr(), sv.size());
        crc = CRC64(data(), size());
    }

    CString::CString(const char* str) {
        ptr = construct(str, CStringUtils::length(str));
        crc = CRC64(data(), size());
    }

    CString::CString(const char c) : rep() {
        ptr = construct(&c, 1);
        crc = CRC64(&c, 1);
    }

    CString::CString(const CString& o) : crc(o.crc) {
        ptr = construct(o.ptr, o.size());
    }

    CString::CString(CString&& o) : crc(o.crc) {
        ptr = construct(o.ptr, o.size());
        if (!o.isSmall()) {
            o.ptr = nullptr;
        }
    }

    TUint CString::size() const {
        return isSmall() ? TUint(rep.small.size) : rep.large.size;
    }

    TUint CString::capacity() const {
        return isSmall() ? sizeof(_LargeData) : rep.large.capacity;
    }

    TBool CString::empty() const {
        return *ptr == 0; // TODO: is there a better way???
    }

    char* CString::data() const {
        return ptr;
    }

    const char* CString::cstr() const {
        return ptr;
    }

    TUint CString::getCRC() const {
        return crc;
    }


    void CString::clear() {
        Memory::clear(ptr, size());

        if (isSmall()) {
            rep.small.size = 0;
        }
        else {
            rep.large.size = 0;
        }
    }

    const char* CString::begin() const {
        return ptr;
    }

    const char* CString::end() const {
        return ptr + size();
    }

    char* CString::begin() {
        return ptr;
    }

    char* CString::end() {
        return ptr + size();
    }

    TBool CString::operator==(const CString& r) const {
        if (size() != r.size()) return kFalse;
        return CStringUtils::compare(ptr, r.ptr, size());
    }

    TBool CString::operator!=(const CString& r) const {
        return !(*this == r);
    }

    CString::operator CStringView() const {
        return { ptr, size() };
    }

    char* CString::find(const CStringView& sv) const {
        return CStringUtils::find(ptr, size(), sv.cstr(), sv.size());
    }

    char* CString::findReverse(const CStringView& sv) const {
        return CStringUtils::reverseFind(ptr, size(), sv.cstr(), sv.size());
    }

    char* CString::findFirst(const CStringView& set) const {
        return CStringUtils::findFirst(ptr, size(), set.cstr(), set.size());
    }

    char* CString::findLast(const CStringView& set) const {
        return CStringUtils::findLast(ptr, size(), set.cstr(), set.size());
    }

    TBool CString::startsWith(const CStringView& str) const {
        return CStringUtils::startsWith(ptr, size(), str.cstr(), str.size());
    }

    TBool CString::endsWith(const CStringView& str) const {
        return CStringUtils::endsWith(ptr, size(), str.cstr(), str.size());
    }

    CString& CString::append(const CStringView& sv) {
        const TUint requiredSize = size() + sv.size();
        if (requiredSize == size() && size()) return *this;

        if (requiredSize > capacity()) {
            auto p = reinterpret_cast<char*>(GAlloc->allocate(requiredSize + 1));
            Memory::copy(p, ptr, size());
            Memory::copy(p + size(), sv.cstr(), sv.size());
            rep.large.strptr = p;
            rep.large.size = requiredSize;
            rep.large.capacity = requiredSize + 1;
            ptr = rep.large.strptr;
        }
        else {
            Memory::copy(ptr + size(), sv.cstr(), sv.size());
            if (isSmall()) {
                rep.small.size = TUint8(requiredSize);
            }
            else {
                rep.large.size = requiredSize;
            }
        }
        crc = CRC64(cstr(), size());
        return *this;
    }

    CString& CString::append(const char c, TUint count) {
        const TUint requiredSize = size() + count;
        if (requiredSize > capacity()) {
            auto p = reinterpret_cast<char*>(GAlloc->allocate(requiredSize + 1));
            Memory::copy(p, ptr, size());
            Memory::fill(p + size(), c, count);
            rep.large.strptr = p;
            rep.large.size = requiredSize;
            rep.large.capacity = requiredSize + 1;
            ptr = rep.large.strptr;
        }
        else {
            if (count == 1) {
                ptr[size()] = c;
            }
            else {
                Memory::fill(ptr + size(), c, count);
            }
            if (isSmall()) {
                rep.small.size = TUint8(requiredSize);
            }
            else {
                rep.large.size = requiredSize;
            }
        }
        ptr[size()] = 0;
        crc = CRC64(cstr(), size());
        return *this;
    }

    CString& CString::operator+=(const CStringView& sv) {
        return append(sv);
    }

    CString& CString::operator+=(const char c){
        return append(c);
    }

    CStringRef CString::toRef() const {
        return makeRef<CString>(ptr, size());
    }
    
    TBool CString::isSmall() const {
        return ptr == rep.small.strbuf;
    }
    
    TBool CString::fitSmall(TUint size) const {
        return size < sizeof(_LargeData);
    }
    
    char* CString::construct(const char* str, TUint size) {
        if (fitSmall(size)) {
            Memory::copy(rep.small.strbuf, str, size);
            rep.small.size = TUint8(size);
            rep.small.strbuf[size] = 0;
            return rep.small.strbuf;
        }
        else {
            auto p = GAlloc->allocate(size + 1);
            NW_ASSERT(p, "Failed to allocate CString(strptr)");
            Memory::copy(p, str, size);
            rep.large.strptr = reinterpret_cast<char*>(p);
            rep.large.size = size;
            rep.large.capacity = size + 1;
            rep.large.strptr[size] = 0;
            return rep.large.strptr;
        }
    }

    
    CStringBuilder::CStringBuilder(CString& ref) : data(ref)
    {
    }

    CStringBuilder& CStringBuilder::operator<<(const char* c_str) {
        data.append(c_str);
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const CStringView& sv) {
        data.append(sv);
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const CString& str) {
        data.append(str);
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const TInt8 v) {
        char buffer[16] = {};
        const TUint len = CStringUtils::signedToString(buffer, v);
        data.append(CStringView(buffer, len));
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const TUint8 v) {
        char buffer[16] = {};
        const TUint len = CStringUtils::unsignedToString(buffer, v);
        data.append(CStringView(buffer, len));
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const TInt16 v) {
        char buffer[16] = {};
        const TUint len = CStringUtils::signedToString(buffer, v);
        data.append(CStringView(buffer, len));
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const TUint16 v) {
        char buffer[16] = {};
        const TUint len = CStringUtils::unsignedToString(buffer, v);
        data.append(CStringView(buffer, len));
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const TInt32 v) {
        char buffer[16] = {};
        const TUint len = CStringUtils::signedToString(buffer, v);
        data.append(CStringView(buffer, len));
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const TUint32 v) {
        char buffer[16] = {};
        const TUint len = CStringUtils::unsignedToString(buffer, v);
        data.append(CStringView(buffer, len));
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const TInt64 v) {
        char buffer[24] = {};
        const TUint len = CStringUtils::signedToString(buffer, v);
        data.append(CStringView(buffer, len));
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const TUint64 v) {
        char buffer[24] = {};
        const TUint len = CStringUtils::unsignedToString(buffer, v);
        data.append(CStringView(buffer, len));
        return *this;
    }

    CStringBuilder& CStringBuilder::operator<<(const TReal v) {
        char buffer[24] = {};
        const TUint len = CStringUtils::realToString(buffer, v);
        data.append(CStringView(buffer, len));
        return *this;
    }


}
