#pragma once

#include <Base/NumericTypes.h>
#include <Base/StringView.h>
#include <Base/TimePoint.h>
#include <Base/MacroUtils.h>

namespace Neowise {

    /** 
    * Simple diagnostics utility class for mainly 
    * logger purposes.
    */
    class NW_API CDiagnostics {
    public:

        void writeString(const char* str);
        void writeString(const wchar_t* wstr);
        void writeString(const char* str, TUint64 len);
        void writeString(const wchar_t* wstr, TUint64 len);
        void writeSigned(const TInt64 v);
        void writeUnsigned(const TUint64 v);
        void writeFloat(const TReal v);

        operator bool() const;
        
    private:
        // TODO: store history of engine's diagnostics
    };

    inline CDiagnostics& operator<<(CDiagnostics& d, const char* str) {
        d.writeString(str);
        return d;
    }
    
    inline CDiagnostics& operator<<(CDiagnostics& d, const wchar_t* wstr) {
        d.writeString(wstr);
        return d;
    }

    inline CDiagnostics& operator<<(CDiagnostics& d, const CStringView& sv) {
        d.writeString(sv.cstr());
        return d;
    }

    inline CDiagnostics& operator<<(CDiagnostics& d, TInt64 i) {
        d.writeSigned(i);
        return d;
    }

    inline CDiagnostics& operator<<(CDiagnostics& d, bool b) {
        d.writeSigned(b);
        return d;
    }

    inline CDiagnostics& operator<<(CDiagnostics& d, TUint64 ui) {
        d.writeUnsigned(ui);
        return d;
    }

    inline CDiagnostics& operator<<(CDiagnostics& d, TInt32 i) {
        d.writeSigned(i);
        return d;
    }

    inline CDiagnostics& operator<<(CDiagnostics& d, TUint32 ui) {
        d.writeUnsigned(ui);
        return d;
    }

    inline CDiagnostics& operator<<(CDiagnostics& d, TReal f) {
        d.writeFloat(f);
        return d;
    }

    extern CDiagnostics GDiag;

    /** 
    * Utility class for profiling code. 
    */
    class NW_API CCodeProfiler {
    public:
        struct TagScopeProfiler {};

        // Records begin time, and name of label.
        CCodeProfiler(const char* name);
        CCodeProfiler(TagScopeProfiler, const char* name);

        // Records end time, calculates estimated 
        // time and prints it through CDiagnostics.
        ~CCodeProfiler();

    private:
        CTimePoint	_begin = {};
        CStringView	_name = {};
    };
}

#define NW_PROFILE_FUNCTION2(name, line) \
    Neowise::CCodeProfiler NW_CONCAT(profiler_, __LINE__)(name)
#define NW_PROFILE_FUNCTION() \
    NW_PROFILE_FUNCTION2(__FUNCTION__, __LINE__)

#define NW_PROFILE_SCOPE2(name) \
    Neowise::CCodeProfiler NW_CONCAT(profiler_scope_, __LINE__)(CCodeProfiler::TagScopeProfiler{}, name)
#define NW_PROFILE_SCOPE(name) \
    NW_PROFILE_SCOPE2(name)

#ifdef NW_SHIP_BUILD
#	undef  NW_PROFILE_FUNCTION
#	define NW_PROFILE_FUNCTION() (void)0
#	undef  NW_PROFILE_SCOPE
#	define NW_PROFILE_SCOPE(name) (void)0
#endif//NW_SHIP_BUILD
