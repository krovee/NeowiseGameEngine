#include <Engine/VulkanRHI/Common.h>

#include <Engine/VulkanRHI/VulkanSurface.h>
#include <Engine/VulkanRHI/VulkanAdapter.h>
#include <Engine/VulkanRHI/DynamicProvider.h>

#include <Platform/Windows/WindowsBase.h>

namespace Neowise {

    const TVector<const char*>& RHIVKUtil::getRequiredInstanceExtensions() {
        static TVector<const char*> sInstanceExtensions = {
            "VK_KHR_win32_surface",

            VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
            VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME,
            VK_KHR_SURFACE_EXTENSION_NAME,
#if NW_BUILD_TYPE_DEBUG
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif//NW_BUILD_TYPE_DEBUG
        };

        return sInstanceExtensions;
    }

    const TVector<const char*>& RHIVKUtil::getRequiredInstanceLayers() {
        static TVector<const char*> sInstanceLayers = {
#if NW_BUILD_TYPE_DEBUG
            "VK_LAYER_LUNARG_standard_validation"
#endif//NW_BUILD_TYPE_DEBUG
        };
        
        return sInstanceLayers;
    }

    const TVector<const char *> &Neowise::RHIVKUtil::getRequiredDeviceExtensions() {
        static TVector<const char*> sDeviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        return sDeviceExtensions;
    }

    TBool RHIVKUtil::createSurfaceFromWindow(const CBaseWindow *window, const CRHIDynamicProviderInterface* prov, IRHISurface& surface) {

        auto vkprov = reinterpret_cast<const CRHIVulkanDynamicProvider*>(prov);

        surface = IRHISurface::make<CRHIVulkanSurface>(
            vkprov->getInstance(),
            VkSurfaceKHR(Platform::Windows::createVulkanSurface(vkprov->getInstance(), Platform::Windows::HWND(window->getNativeHandle())))
        );

        return kTrue;
    }

}