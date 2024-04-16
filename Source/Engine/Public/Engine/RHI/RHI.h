#pragma once

#include <Engine/RHI/Common.h>
#include <Engine/RHI/RHIAdapter.h>
#include <Engine/BaseWindow.h>

namespace Neowise {
    
    class NW_API CRHIDynamicProviderInterface : public RHIBase<CRHIDynamicProviderInterface> {
    public:
        virtual  ~CRHIDynamicProviderInterface() = default;
        CRHIDynamicProviderInterface() = default;

        virtual IRHISurface createSurface(const CBaseWindow* window) = 0;
        virtual IRHIAdapter createAdapter(const SRHIAdapterSpecification& specs) = 0;
        virtual IRHIAdapter createAdapter(const SRHIAdapterSpecification& specs, const IRHISurface& requredSurface) = 0;

        NW_RHI_CLASS_DECLARATION(CRHIDynamicProviderInterface)
    };

    template<class T, class...Args>
    inline auto RHIMakeProvider(Args&&...args) {
        return IRHIDynamicProvider::make<T>(forward<Args>(args)...);
    }

    NW_API IRHIDynamicProvider RHIMakeVulkanProvider();

}
