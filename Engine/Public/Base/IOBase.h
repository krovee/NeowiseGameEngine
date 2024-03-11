#pragma once

#include <Base/NumericTypes.h>
#include <Base/UUID.h>

namespace Neowise {
	/** 
	* Base class for any Input-Output class.
	*/
	class NW_API CIOBase {
	public:
		virtual void* getHandle() const { return nullptr; }

		virtual void write(const char* data) {}
		virtual void write(const char* data, uint64 len) {}
		virtual void writeFmt(const char* fmt, ...) {}
		virtual void write(const wchar_t* data) {}
		virtual void write(const wchar_t* data, uint64 len) {}
		virtual void writeFmt(const wchar_t* fmt, ...) {}

	protected:
		inline CIOBase(CUUID ioid) : _ioid(ioid) {}

		CUUID _ioid = CUUID::INVALID;
	};
}
