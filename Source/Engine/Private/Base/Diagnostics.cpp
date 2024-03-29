#include <Base/Common.h>
#include <Base/Clock.h>
#include <Base/StringUtils.h>

#include <Platform/PlatformConsole.h>

namespace Neowise {
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

#   if NW_OS_TYPE_WIN32
    CCodeProfiler::CCodeProfiler(const char* name) 
        : _name(name, 9, CStringUtils::length(name)), _begin(CClock::now())
    {
    }
#   else
    CCodeProfiler::CCodeProfiler(const char* name) 
        : _begin(CClock::now()), _name(name, CStringUtils::length(name))
    {
    }
#   endif

    CCodeProfiler::CCodeProfiler(TagScopeProfiler, const char* name)
        : _begin(CClock::now()), _name(name)
    {
    }

    CCodeProfiler::~CCodeProfiler() {
        const auto end = CClock::now();
        
        const auto elapsed = CTimePoint::normalize(end - _begin);
        const auto ms = elapsed.getMilliseconds();
        const char* meas = ms > 1500 ? "s" : "ms";
        const auto timev = ms > 1500 ? elapsed.getSeconds() : ms;

        GDiag << "[PROFILER]: " << timev << meas << "\t" << _name << "()\n";
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