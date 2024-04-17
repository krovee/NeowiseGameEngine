#pragma once

#include <Engine/RHI/Common.h>

namespace Neowise {

    class NW_API CRHISurfaceInterface : public RHIBase {
    public:
        virtual ~CRHISurfaceInterface() = default;
        CRHISurfaceInterface() = default;

        NW_RHI_CLASS_DECLARATION(CRHISurfaceInterface)
    };

}
