#pragma once

#include <Engine/RHI/Common.h>

namespace Neowise {

    class CRHISurfaceInterface;

    using IRHISurface = RHIInterface<CRHISurfaceInterface>;

    class NW_API CRHISurfaceInterface : public RHIBase<CRHISurfaceInterface> {
    public:
        virtual ~CRHISurfaceInterface() = default;
        CRHISurfaceInterface() = default;

        NW_RHI_CLASS_DECLARATION(CRHISurfaceInterface)
    };

}
