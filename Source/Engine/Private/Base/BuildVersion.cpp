#include <Base/BuildVersion.h>
#include <Base/Hash.h>

namespace Neowise {
    namespace {
        constexpr const auto _dateTimeStr = __DATE__ " " __TIME__;
        

        const TUint64 _dateHash = CHash()(_dateTimeStr, 20);
    }

    CBuildVersion buildVersion = {};

    CBuildVersion::CBuildVersion() : _number(_dateHash)
    {
    }

    CBuildVersion::operator TUint() const {
        return _number;
    }

    TUint64 CBuildVersion::get() const {
        return _number;
    }

}
