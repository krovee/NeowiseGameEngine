#include <Base/StringView.h>
#include <Base/StringUtils.h>
#include <Base/Templated.h>

namespace Neowise {
    CStringView::CStringView(const char* cstr)
        : _str(cstr), _size(CStringUtils::length(cstr))
    {
    }

    CStringView::CStringView(const char* cstr, TUint64 size)
        : _str(cstr), _size(size) 
    {
    }

    CStringView::CStringView(const char* cstr, TUint64 offset, TUint64 size)
        : _str(cstr + offset), _size(size - offset) 
    {
    }

    CStringView::CStringView(const CStringView& sv, TUint64 offset)
        : _str(sv.cstr() + offset), _size(sv.size() - offset) 
    {
    }

    const char* CStringView::cstr() const {
        return _str;
    }

    TUint64 CStringView::size() const {
        return _size;
    }

    TBool CStringView::empty() const {
        return _size == 0;
    }

    const CUUID CStringView::getUUID() const {
        return CUUID(_str, _size);
    }

    const char* CStringView::begin() const {
        return _str;
    }

    const char* CStringView::end() const {
        return _str + _size;
    }

    char* CStringView::find(const CStringView& sv) const {
        return CStringUtils::find(_str, _size, sv._str, sv._size);
    }

    char* CStringView::findReverse(const CStringView& sv) const {
        return CStringUtils::reverseFind(_str, _size, sv._str, sv._size);
    }

    char* CStringView::findFirst(const CStringView& set) const {
        return CStringUtils::findFirst(_str, _size, set._str, set._size);
    }

    char* CStringView::findLast(const CStringView& set) const {
        return CStringUtils::findLast(_str, _size, set._str, set._size);
    }

    TBool CStringView::startsWith(const CStringView& str) const {
        return CStringUtils::startsWith(_str, _size, str._str, str._size);
    }

    TBool CStringView::endsWith(const CStringView& str) const {
        return CStringUtils::endsWith(_str, _size, str._str, str._size);
    }

    TBool CStringView::operator==(const CStringView& r) const {
        if (_size != r._size) return kFalse;
        return CStringUtils::compare(_str, r._str, _size);
    }

    TBool CStringView::operator!=(const CStringView& r) const{
        return !(*this == r);
    }

    TBool CStringView::compareSizesLess(const CStringView& a, const CStringView& b) {
        return a._size < b._size;
    }

    TBool CStringView::compareSizesGreater(const CStringView& a, const CStringView& b) {
        return a._size > b._size;
    }


}
