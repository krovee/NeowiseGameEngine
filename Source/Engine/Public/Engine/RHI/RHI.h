#pragma once

#include <Engine/RHI/Common.h>

namespace Neowise {
	
    class NW_API CRHIDynamicProviderInterface {
    public:
        virtual  ~CRHIDynamicProviderInterface() = default;
        constexpr CRHIDynamicProviderInterface() = default;

        constexpr CRHIDynamicProviderInterface(const ERHIProviderClass _class) : _providerClass(_class)
        {}

        ERHIProviderClass getClass() const;
    private:
        const ERHIProviderClass _providerClass = E_RHI_PROVIDER_CLASS_UNDEFINED;
    };

    using IRHIDynamicProvider = Scope<CRHIDynamicProviderInterface>;

    template<class T, class...Args>
    inline auto RHIMakeProvider(Args&&...args) {
        return makeScope<T>(forward<Args>(args)...).template cast<CRHIDynamicProviderInterface>();
    }

    NW_API IRHIDynamicProvider RHIMakeVulkanProvider();

}
