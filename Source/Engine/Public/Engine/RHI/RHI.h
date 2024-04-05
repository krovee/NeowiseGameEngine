#pragma once

#include <Engine/RHI/Common.h>

namespace Neowise {
    
    class CRHIAdapterInterface;
    using IRHIAdapter = Scope<CRHIAdapterInterface>;

    class NW_API CRHIDynamicProviderInterface {
    public:
        virtual  ~CRHIDynamicProviderInterface() = default;
        constexpr CRHIDynamicProviderInterface() = default;

        virtual IRHIAdapter createAdapter() = 0;

        NW_RHI_CLASS_DECLARATION(CRHIDynamicProviderInterface)
    };

    using IRHIDynamicProvider = Scope<CRHIDynamicProviderInterface>;

    template<class T, class...Args>
    inline auto RHIMakeProvider(Args&&...args) {
        return makeScope<T>(forward<Args>(args)...).template cast<CRHIDynamicProviderInterface>();
    }

    NW_API IRHIDynamicProvider RHIMakeVulkanProvider();

}
