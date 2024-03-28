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
		CStringView(const char* cstr, uint64 size);
		CStringView(const char* cstr, uint64 offset, uint64 size);
		CStringView(const CStringView& sv, uint64 offset);
		CStringView(const CStringView& sv) = default;
		CStringView(CStringView&& sv) = default;
		CStringView& operator=(const CStringView& sv) = default;
		CStringView& operator=(CStringView&& sv) = default;

		~CStringView() = default;

		const char* cstr() const;
		uint64 size() const;
		bool empty() const;
		const CUUID getUUID() const; // WARN: Generated every call

		const char* begin() const;
		const char* end() const;

		char* find(const CStringView& sv) const;
		char* findReverse(const CStringView& sv) const;
		char* findFirst(const CStringView& set) const;
		char* findLast(const CStringView& set) const;
		bool  startsWith(const CStringView& str) const;
		bool  endsWith(const CStringView& str) const;

		bool operator==(const CStringView& r) const;
		bool operator!=(const CStringView& r) const;

		static bool compareSizesLess(const CStringView& a, const CStringView& b);
		static bool compareSizesGreater(const CStringView& a, const CStringView& b);
	private:
		const char*	_str = nullptr;
		uint64		_size = 0;
		// CUUID		_uuid = {};
	};

}
