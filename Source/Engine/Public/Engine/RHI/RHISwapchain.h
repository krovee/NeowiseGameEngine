#pragma once

#include <Engine/RHI/Common.h>

namespace Neowise {

    struct SRHISwapchainSpecification {
        const FVec2 extent = {};
        EVerticalSynchronization vsync = E_VERTICAL_SYNCHRONIZATION_FULL; // NOTE: by default cap framerate to monitor freq (Hz).
    };

    class CRHISwapchainInterface : public RHIBase {
    public:
        virtual ~CRHISwapchainInterface() = default;

        NW_RHI_CLASS_DECLARATION(CRHISwapchainInterface)
    };

}
