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
		CString(const char* str, uint size);
		CString(const CStringView& sv);
		CString(const char* str);
		CString(const char c);

		CString(const CString&);
		CString(CString&&);
		CString& operator=(const CString&) = default;
		CString& operator=(CString&&) = default;

		uint size() const;
		uint capacity() const;
		bool empty() const;
		char* data() const;
		const char* cstr() const;
		uint getCRC() const;
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
		CString& append(const char c, uint count = 1);

		CString& operator+=(const CStringView& sv);
		CString& operator+=(const char c);

		CStringRef toRef() const;
	private:
		bool isSmall() const;
		bool fitSmall(uint size) const;
		char* construct(const char* str, uint size);

	private:
		struct NW_API _LargeData {
			constexpr _LargeData() = default;

			char*	strptr = nullptr;
			uint	size = 0;
			uint	capacity = 0;
		};

		struct NW_API _SmallData {
			constexpr _SmallData() = default;
			
			char	strbuf[sizeof(_LargeData) - sizeof(uint8)] = {};
			uint8	size = 0;
		};

		char*	ptr = nullptr;
		uint	crc = {};
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
		static uint get(const CString& str) {
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
		CStringBuilder& operator<<(const int8 v);
		CStringBuilder& operator<<(const uint8 v);
		CStringBuilder& operator<<(const int16 v);
		CStringBuilder& operator<<(const uint16 v);
		CStringBuilder& operator<<(const int32 v);
		CStringBuilder& operator<<(const uint32 v);
		CStringBuilder& operator<<(const int64 v);
		CStringBuilder& operator<<(const uint64 v);
		CStringBuilder& operator<<(const real v);

	private:
		CString& data;
	};
}
