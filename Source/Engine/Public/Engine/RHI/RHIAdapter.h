#pragma once

#include <Engine/RHI/Common.h>

namespace Neowise {

    class CRHIAdapterInterface;

    using IRHIAdapter = Scope<CRHIAdapterInterface>;

    class NW_API CRHIAdapterInterface {
    public:
        virtual ~CRHIAdapterInterface() = default;

        NW_RHI_CLASS_DECLARATION(CRHIAdapterInterface)
    };

}
