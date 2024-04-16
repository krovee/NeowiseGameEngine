#include <Engine/VulkanRHI/VulkanSurface.h>
#include <Base/DynamicLibrary.h>

namespace Neowise {
    Neowise::CRHIVulkanSurface::~CRHIVulkanSurface() {
        if (surface && destroySurfaceKHR) {
            destroySurfaceKHR(instance, surface, nullptr);
        }
    }

    CRHIVulkanSurface::CRHIVulkanSurface(VkInstance _instance, VkSurfaceKHR _surface) : instance(_instance), surface(_surface) {
        
        auto vk = CDynamicLibrary::load(NW_VK_LIBRARY_NAME);
        PFN_vkGetInstanceProcAddr getInstanceProcAddr = 
            vk->getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");

        destroySurfaceKHR = (PFN_vkDestroySurfaceKHR)getInstanceProcAddr(instance, "vkDestroySurfaceKHR");
        getPhysicalDeviceSurfaceSupportKHR = 
            (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)getInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceSupportKHR");
        getPhysicalDeviceSurfaceCapabilitiesKHR = 
            (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)getInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
        getPhysicalDeviceSurfaceFormatsKHR =
            (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)getInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
        getPhysicalDeviceSurfacePresentModesKHR = 
            (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)getInstanceProcAddr(instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
    }

    VkSurfaceKHR CRHIVulkanSurface::getSurface() const {
        return surface;
    }

    TBool Neowise::CRHIVulkanSurface::getPhysicalDeviceSupport(VkPhysicalDevice pd, TUint32 queueIdx, VkBool32 *pSupported) const {
        return VK_SUCCESS == getPhysicalDeviceSurfaceSupportKHR(pd, queueIdx, surface, pSupported);
    }

    TBool Neowise::CRHIVulkanSurface::getPhysicalDeviceCapabilities(VkPhysicalDevice pd, VkSurfaceCapabilitiesKHR *pSurfaceCaps) const {
        return VK_SUCCESS == getPhysicalDeviceSurfaceCapabilitiesKHR(pd, surface, pSurfaceCaps);
    }

    TBool Neowise::CRHIVulkanSurface::getPhysicalDeviceFormats(VkPhysicalDevice pd, TUint32 *pCount, VkSurfaceFormatKHR *pFormats) const {
        return VK_SUCCESS == getPhysicalDeviceSurfaceFormatsKHR(pd, surface, pCount, pFormats);
    }

    TBool Neowise::CRHIVulkanSurface::getPhysicalDevicePresentModes(VkPhysicalDevice pd, TUint32 *pCount, VkPresentModeKHR *pModes) const {
        return VK_SUCCESS == getPhysicalDeviceSurfacePresentModesKHR(pd, surface, pCount, pModes);
    }
}