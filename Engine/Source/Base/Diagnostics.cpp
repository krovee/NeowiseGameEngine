#include <Base/Common.h>
#include <Base/Clock.h>
#include <Base/StringUtils.h>

#include <Platform/PlatformConsole.h>

namespace Neowise {

	namespace {
        char* itoa(int value, char* result, int base) {
            // check that the base if valid
            if (base < 2 || base > 36) { *result = '\0'; return result; }

            char* ptr = result, * ptr1 = result, tmp_char;
            int tmp_value;

            do {
                tmp_value = value;
                value /= base;
                *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
            } while (value);

            // Apply negative sign
            if (tmp_value < 0) *ptr++ = '-';
            *ptr-- = '\0';

            // Reverse the string
            while (ptr1 < ptr) {
                tmp_char = *ptr;
                *ptr-- = *ptr1;
                *ptr1++ = tmp_char;
            }
            return result;
        }
	}

	CDiagnostics GDiag;

	void CDiagnostics::writeString(const char* str) {
		Platform::GConsole.write(str);
	}
	
	void CDiagnostics::writeString(const wchar_t* wstr) {
		Platform::GConsole.write(wstr);
	}

    void CDiagnostics::writeString(const char* str, uint64 len) {
        Platform::GConsole.write(str, len);
    }

    void CDiagnostics::writeString(const wchar_t* wstr, uint64 len) {
        Platform::GConsole.write(wstr, len);
    }

	void CDiagnostics::writeSigned(const int64 v) {
        Platform::GConsole.writeFmt("%lld", v);
	}

	void CDiagnostics::writeUnsigned(const uint64 v) {
        Platform::GConsole.writeFmt("%llu", v);
	}

    void CDiagnostics::writeFloat(const real v) {
        Platform::GConsole.writeFmt("%.4f", v);
    }

    CDiagnostics::operator bool() const {
        return Platform::GConsole.getHandle();
    }

#ifndef NW_SHIP_BUILD

    CCodeProfiler::CCodeProfiler(const char* name) 
        : _name(name, 9, CStringUtils::length(name)), _begin(CClock::now())
    {
    }

    CCodeProfiler::CCodeProfiler(TagScopeProfiler, const char* name)
        : _name(name), _begin(CClock::now())
    {
    }

    CCodeProfiler::~CCodeProfiler() {
        const auto end = CClock::now();
        
        const auto elapsed = CTimePoint::normalize(end - _begin);

        GDiag << "[PROFILER]: " << elapsed.getMilliseconds() << "ms\t" << _name << "()\n";
    }

#else 

    CCodeProfiler::CCodeProfiler(const char* name)
    {
    }

    CCodeProfiler::~CCodeProfiler() 
    {
    }


#endif

}
