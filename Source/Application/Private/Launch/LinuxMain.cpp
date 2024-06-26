#include <Base/MacroUtils.h>

#if NW_OS_TYPE_LINUX

#include <Launch/SecureMain.h>

auto main(int argc, char **argv) -> int {
    using namespace Neowise;

    CSecureMain secMain;

    secMain.parseCmdLine(argc, argv);

    return secMain.executeMain();
}

#endif
