#include <Engine/VulkanRHI/Common.h>

namespace Neowise {

    const CVector<const char*>& RHIVKUtil::getRequiredInstanceExtensions() {
        static CVector<const char*> sInstanceExtensions = {
            "VK_KHR_surface",
            "VK_KHR_xcb_surface",
            "VK_KHR_xlib_surface",
            "VK_KHR_wayland_surface",
            "VK_EXT_debug_utils",
            "VK_KHR_get_physical_device_properties2"
        };

        return sInstanceExtensions;
    }

    const CVector<const char*>& RHIVKUtil::getRequiredInstanceLayers() {
        static CVector<const char*> sInstanceLayers = {
#if NW_BUILD_TYPE_DEBUG
            "VK_LAYER_LUNARG_standard_validation"
#endif
        };
        
        return sInstanceLayers;
    }

}
