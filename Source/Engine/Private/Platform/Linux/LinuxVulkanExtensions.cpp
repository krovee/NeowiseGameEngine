#include <Engine/VulkanRHI/Common.h>

namespace Neowise {

    const TVector<const char*>& RHIVKUtil::getRequiredInstanceExtensions() {
        static TVector<const char*> sInstanceExtensions = {
            "VK_KHR_surface",
            "VK_KHR_xcb_surface",
            "VK_KHR_xlib_surface",
            "VK_KHR_wayland_surface",
            "VK_EXT_debug_utils",
            "VK_KHR_get_physical_device_properties2"
        };

        return sInstanceExtensions;
    }

    const TVector<const char*>& RHIVKUtil::getRequiredInstanceLayers() {
        static TVector<const char*> sInstanceLayers = {
#if NW_BUILD_TYPE_DEBUG
            "VK_LAYER_LUNARG_standard_validation"
#endif
        };
        
        return sInstanceLayers;
    }

}
